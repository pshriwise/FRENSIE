//---------------------------------------------------------------------------//
//!
//! \file   ParticleSimulationManager_def.hpp
//! \author Alex Robinson
//! \brief  The particle simulation manager class definition.
//!
//---------------------------------------------------------------------------//

#ifndef PARTICLE_SIMULATION_MANAGER_DEF_HPP
#define PARTICLE_SIMULATION_MANAGER_DEF_HPP

// FACEMC Includes
#include "ContractException.hpp"
#include "GeometryHandlerTraits.hpp"

namespace FACEMC{

// Get an instance of the simulation manager (singleton pattern)
template<typename GeometryHandler, 
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename MaterialHandler,
	 typename RandomNumberGenerator>
ParticleSimulationManager<GeometryHandler,
			  SourceHandler,
			  EstimatorHandler,
			  MaterialHandler,
			  RandomNumberGenerator>::Pointer
ParticleSimulationManager<GeometryHandler,
			  SourceHandler,
			  EstimatorHandler,
			  MaterialHandler,
			  RandomNumberGenerator>::getInstance()
{
  if( ParticleSimulationManager::instance.is_null() )
    ParticleSimulationManager::instance.reset( 
					     new ParticleSimulationManager() );
  return instance;
}

// Set the number of particle histories to simulate
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename MaterialHandler,
	 typename RandomNumberGenerator>
void ParticleSimulation<GeometryHandler,
			SourceHandler,
			EstimatorHandler,
			MaterialHandler,
			RandomNumberGenerator>::setNumberOfParticleHistores( 
					   const unsigned number_of_histories )
{
  // At least one history must be simulated
  testPrecondition( number_of_histories > 0 );
  
  d_history_number_wall = number_of_histories;
}

// Set the number of particle histories to simulate
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler,
	 typename RandomNumberGenerator>
void ParticleSimulation<GeometryHandler,
			SourceHandler,
			EstimatorHandler,
			CollisionHandler>::runSimulation()
{
  // Get instances of the handlers
  GHT::GeometryHandlerPtr geometry_handler = GHT::getInstance();
  SHT::SourceHandlerPtr source_handler = SHT::getInstance();
  
  std::vector<ParticleState> particle_bank;

  for( unsigned history = 0; history <= d_history_number_wall; ++history )
  {
    // Initialize the root particle for this history
    ParticleState particle( history );

    // Sample the starting state from the source handler
    SHT::sampleStartingParticleState( particle );

    // Determine the starting cell from the  geometry handler
    try{
      GHT::getCellContainingPoint( geometry_handler, particle );
    }
    // A lost particle will result in an exception
    catch( std::runtime_exception& exception )
    {
      std::cerr << exception.what() << std::endl;
      
      continue;
    }

    EHT::updateEstimatorsAtSourcePoint( particle );

    // Initialize the particle bank for this history
    particle_bank.push_back( particle );

    // This history only ends when the particle bank is empty
    while( particle_bank.size() > 0 )
    {
      ParticleState particle = particle_bank.back();
      particle_bank.pop_back();

      // Simulate the particle
      simulateParticle( particle, particle_bank );      
    }
  }
}

// Set the number of particle histories to simulate
template<typename GeometryHandler,
	 typename SourceHandler,
	 typename EstimatorHandler,
	 typename CollisionHandler,
	 typename RandomNumberGenerator>
void ParticleSimulation<GeometryHandler,
			SourceHandler,
			EstimatorHandler,
			CollisionHandler>::simulateParticle( 
				    ParticleState& particle,
				    std::vector<ParticleState>& particle_bank )
{
  // Get instances of the handlers
  GHT::GeometryHandlerPtr geometry_handler = GHT::getInstance();
  EHT::EstimatorHandlerPtr estimator_handler= EHT::getInstance();
  CHT::CollisionHandlerPtr collision_handler = CHT::getInstance();

  GHT::SurfaceHandle surface_hit;
  double distance_to_surface_hit;
  double mfp_to_surface_hit;
  double remaining_subtrack_mfp;
  double cell_total_macro_cross_section;
  
  while( !particle.isLost() && !particle.isGone() )
  {
    // Sample the mfp traveled by the particle on this subtrack
    remaining_subtrack_mfp = sampleMFP( collision_handler );
    
    // Trace the particle until the necessary number of mfps have be traveled
    while( true )
    {
      // Fire a ray at the cell currently containing the particle
      try{
	fireRay( geometry_handler,
		 particle,
		 surface_hit,
		 distance_to_surface_hit );
      }
      // A lost particle will result in an exception
      catch( std::runtime_exception& exception )
      {
	std::cerr << exception.what() << std::endl;
	particle.isLost();
	
	break;
      }

      // Get the total cross section for the cell
      cell_total_macro_cross_section = 
	CHT::getTotalMacroscopicCrossSection( particle.getCell() );

      // Convert the distance to the surface to mfp
      mfp_to_surface_hit = 
	distance_to_surface_hit*cell_total_macro_cross_section;

      if( mfp_to_surface_hit < remaining_subtrack_mfp )
      {
	// Advance the particle to the cell boundary
	particle.advance( distance_to_surface_hit );

	// Get the surface normal at the intersection point
	double surface_normal[3];
	GHT::getSurfaceNormal( surface_hit,
			       particle,
			       surface_normal );			       

	CellHandle current_cell = particle_state.getCell();
	// Find the cell on the other side of the surface hit
	try{
	  getNextCell( geometry_handler, surface_hit, particle );
	}
	// A lost particle will result in an exception
	catch( std::runtime_error& exception )
	{
	  std::cerr << exception.what() << std::endl;
	  particle.setAsLost();
	  
	  break;
	}

	// Update track length estimators, current estimators before crossing 
	// the cell boundary
	// Note: Both the current cell and next cell need to be known for 
	//       pulse height tallies
	EHT::updateEstimatorsAtIntersection( particle_state,
					     current_cell,
					     surface_hit,
					     distance_to_surface_hit,
					     surface_normal );

	// Check if a termination cell was encountered
	if( isTerminationCell( geometry_handler, particle.cell() ) )
	{
	  particle.setAsGone();

	  break;
	}

	// Update the remaining subtrack mfp
	remaining_subtrack_mfp -= mfp_to_surface_hit;
      } 
      
      // A collision occurs in this cell
      else
      {
	// Advance the particle to the collision site
	double distance = 
	  remaining_subtrack_mfp/cell_total_macro_cross_section;
	
	particle.advance( distance );
	
	// Update collision and track length estimators before undergoing a 
	// collision
	EHT::updateEstimatorsAtCollision( particle,
					  distance,
					  1.0/cell_total_macro_cross_section );

	// Undergo a collision with the material in the cell
	undergoCollision( collision_handler, particle );

	// This subtrack is finished
	break;
      }
    }	     
  }
  
}

} // end FACEMC namespace

#endif // end PARTICLE_SIMULATION_MANAGER_DEF_HPP

//---------------------------------------------------------------------------//
// end ParticleSimulationManager_def.hpp
//---------------------------------------------------------------------------//