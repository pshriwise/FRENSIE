//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronProbeState.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron probe state unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronProbeState.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Get the particle type
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, getParticleType )
{
  MonteCarlo::AdjointElectronProbeState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getParticleType(), 
		       MonteCarlo::ADJOINT_ELECTRON_PROBE );
}

//---------------------------------------------------------------------------//
// Get the particle speed
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, getSpeed )
{
  MonteCarlo::AdjointElectronProbeState particle( 1ull );

  TEST_EQUALITY_CONST( particle.getSpeed(), 
		       0.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electron probe behaves correctly when its energy is set
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, setEnergy )
{
  MonteCarlo::AdjointElectronProbeState particle_a( 1ull );

  TEST_ASSERT( !particle_a.isGone() );

  particle_a.setEnergy( 1.0 );

  TEST_ASSERT( !particle_a.isGone() );

  particle_a.setEnergy( 2.0 );

  TEST_ASSERT( particle_a.isGone() );

  MonteCarlo::AdjointElectronProbeState particle_b( particle_a, true );

  TEST_ASSERT( !particle_b.isGone() );

  particle_b.setEnergy( 10.0 );

  TEST_ASSERT( particle_b.isGone() );
}

//---------------------------------------------------------------------------//
// Advance the particle along its direction by a specified distance
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, advance )
{
  const double position[3] = {1.0, 1.0, 1.0};
  const double direction[3] = {0.5773502691896258, 
			       0.5773502691896258,
			       0.5773502691896258};
  
  MonteCarlo::AdjointElectronProbeState particle( 1ull );
  particle.setPosition( position );
  particle.setDirection( direction );
  particle.setEnergy( 1.0 );
  particle.setTime( 0.0 );
  
  particle.advance( 1.7320508075688772 );

  TEST_FLOATING_EQUALITY( particle.getXPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getYPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getZPosition(), 2.0, 1e-12 );
  TEST_FLOATING_EQUALITY( particle.getTime(), 5.7774996046392e-11, 1e-12 );
}

//---------------------------------------------------------------------------//
// Create new particles
TEUCHOS_UNIT_TEST( AdjointElectronProbeState, copy_constructor )
{
  MonteCarlo::AdjointElectronProbeState particle_gen_a( 1ull );
  particle_gen_a.setPosition( 1.0, 1.0, 1.0 );
  particle_gen_a.setPosition( 0.0, 0.0, 1.0 );
  particle_gen_a.setEnergy( 1.0 );
  particle_gen_a.setTime( 1.0 );
  particle_gen_a.incrementCollisionNumber();
  particle_gen_a.setWeight( 0.5 );

  MonteCarlo::AdjointElectronProbeState particle_gen_a_copy( particle_gen_a );
  
  TEST_EQUALITY( particle_gen_a_copy.getXPosition(), 
		 particle_gen_a.getXPosition() );
  TEST_EQUALITY( particle_gen_a_copy.getYPosition(), 
		 particle_gen_a.getYPosition() );
  TEST_EQUALITY( particle_gen_a_copy.getZPosition(), 
		 particle_gen_a.getZPosition() );
  TEST_EQUALITY( particle_gen_a_copy.getXDirection(), 
		 particle_gen_a.getXDirection() );
  TEST_EQUALITY( particle_gen_a_copy.getYDirection(), 
		 particle_gen_a.getYDirection() );
  TEST_EQUALITY( particle_gen_a_copy.getZDirection(), 
		 particle_gen_a.getZDirection() );
  TEST_EQUALITY( particle_gen_a_copy.getEnergy(),
		 particle_gen_a.getEnergy() );
  TEST_EQUALITY( particle_gen_a_copy.getSpeed(),
		 particle_gen_a.getSpeed() );
  TEST_EQUALITY( particle_gen_a_copy.getTime(),
		 particle_gen_a.getTime() );
  TEST_EQUALITY( particle_gen_a_copy.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  TEST_EQUALITY( particle_gen_a_copy.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber() );
  TEST_EQUALITY( particle_gen_a_copy.getWeight(),
		 particle_gen_a.getWeight() );

  // Create a second generation particle with the same collision number
  MonteCarlo::AdjointElectronProbeState particle_gen_b( particle_gen_a, true );

  TEST_EQUALITY( particle_gen_b.getXPosition(), 
		 particle_gen_a.getXPosition() );
  TEST_EQUALITY( particle_gen_b.getYPosition(), 
		 particle_gen_a.getYPosition() );
  TEST_EQUALITY( particle_gen_b.getZPosition(), 
		 particle_gen_a.getZPosition() );
  TEST_EQUALITY( particle_gen_b.getXDirection(), 
		 particle_gen_a.getXDirection() );
  TEST_EQUALITY( particle_gen_b.getYDirection(), 
		 particle_gen_a.getYDirection() );
  TEST_EQUALITY( particle_gen_b.getZDirection(), 
		 particle_gen_a.getZDirection() );
  TEST_EQUALITY( particle_gen_b.getEnergy(),
		 particle_gen_a.getEnergy() );
  TEST_EQUALITY( particle_gen_b.getTime(),
		 particle_gen_a.getTime() );
  TEST_EQUALITY( particle_gen_b.getCollisionNumber(),
		 particle_gen_a.getCollisionNumber() );
  TEST_EQUALITY( particle_gen_b.getGenerationNumber(),
		 particle_gen_a.getGenerationNumber()+1u );
  TEST_EQUALITY( particle_gen_b.getWeight(),
		 particle_gen_a.getWeight() );  

  // Create a third generation particle and reset the collision counter
  MonteCarlo::AdjointElectronProbeState particle_gen_c( particle_gen_b, true, true );

  TEST_EQUALITY( particle_gen_c.getXPosition(), 
		 particle_gen_b.getXPosition() );
  TEST_EQUALITY( particle_gen_c.getYPosition(), 
		 particle_gen_b.getYPosition() );
  TEST_EQUALITY( particle_gen_c.getZPosition(), 
		 particle_gen_b.getZPosition() );
  TEST_EQUALITY( particle_gen_c.getXDirection(), 
		 particle_gen_b.getXDirection() );
  TEST_EQUALITY( particle_gen_c.getYDirection(), 
		 particle_gen_b.getYDirection() );
  TEST_EQUALITY( particle_gen_c.getZDirection(), 
		 particle_gen_b.getZDirection() );
  TEST_EQUALITY( particle_gen_c.getEnergy(),
		 particle_gen_b.getEnergy() );
  TEST_EQUALITY( particle_gen_c.getTime(),
		 particle_gen_b.getTime() );
  TEST_EQUALITY_CONST( particle_gen_c.getCollisionNumber(), 0u );
  TEST_EQUALITY( particle_gen_c.getGenerationNumber(),
		 particle_gen_b.getGenerationNumber()+1u );
  TEST_EQUALITY( particle_gen_c.getWeight(),
		 particle_gen_b.getWeight() );
}

//---------------------------------------------------------------------------//
// end tstAdjointElectronProbeState.cpp
//---------------------------------------------------------------------------//

