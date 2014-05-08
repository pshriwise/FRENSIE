//---------------------------------------------------------------------------//
//!
//! \file   tstCellTrackLengthFluxEstimator.cpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "CellTrackLengthFluxEstimator.hpp"
#include "ModuleTraits.hpp"
#include "PhotonState.hpp"

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name ) \
  using namespace FACEMC;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WeightMultiplier ) \
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, WeightAndEnergyMultiplier)\

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Set the energy bins (and response functions)
void setEstimatorBins( Teuchos::RCP<FACEMC::Estimator>& estimator )
{
  // Set the energy bins
  Teuchos::Array<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1.0;

  estimator->setBinBoundaries<FACEMC::ENERGY_DIMENSION>(energy_bin_boundaries);
}

// Initialize the estimator
template<typename CellTrackLengthFluxEstimator>
void initializeCellTrackLengthFluxEstimator( 
			Teuchos::RCP<CellTrackLengthFluxEstimator>& estimator )
{  
  // Set the entity ids
  Teuchos::Array<FACEMC::Traits::ModuleTraits::InternalCellHandle> 
    cell_ids( 2 );
  cell_ids[0] = 0;
  cell_ids[1] = 1;

  Teuchos::Array<double> cell_volumes( 2 );
  cell_volumes[0] = 1.0;
  cell_volumes[1] = 2.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new CellTrackLengthFluxEstimator( 0ull, 
						     estimator_multiplier,
						     cell_ids,
						     cell_volumes ) );

  Teuchos::Array<FACEMC::ParticleType> particle_types( 1 );
  particle_types[0] = FACEMC::PHOTON;
  
  estimator->setParticleTypes( particle_types );

  Teuchos::RCP<FACEMC::Estimator> estimator_base = 
    Teuchos::rcp_dynamic_cast<FACEMC::Estimator>( estimator );
  
  // Set the estimator bins (and response functions)
  setEstimatorBins( estimator_base );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellTrackLengthFluxEstimator,
				   getNumberOfBins,
				   ContributionMultiplierPolicy )
{
  typedef FACEMC::CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>
    CellTrackLengthFluxEstimator;

  Teuchos::RCP<CellTrackLengthFluxEstimator> estimator;
  initializeCellTrackLengthFluxEstimator<CellTrackLengthFluxEstimator>( 
								   estimator );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 2u );

  Teuchos::Array<double> cosine_bins( 3 );
  cosine_bins[0] = -1.0;
  cosine_bins[1] = 0.0;
  cosine_bins[2] = 1.0;

  estimator->template setBinBoundaries<FACEMC::COSINE_DIMENSION>( cosine_bins);
  
  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 4u );

  Teuchos::Array<double> time_bins( 3 );
  time_bins[0] = 0.0;
  time_bins[1] = 0.5;
  time_bins[2] = 1.0;

  estimator->template setBinBoundaries<FACEMC::TIME_DIMENSION>( time_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 8u );

  Teuchos::Array<unsigned> coll_bins( 2 );
  coll_bins[0] = 0u;
  coll_bins[1] = std::numeric_limits<unsigned>::max();

  estimator->template setBinBoundaries<FACEMC::COLLISION_NUMBER_DIMENSION>( 
							       coll_bins );

  TEST_EQUALITY_CONST( estimator->getNumberOfBins(), 16u );
}

UNIT_TEST_INSTANTIATION( CellTrackLengthFluxEstimator, getNumberOfBins );

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CellTrackLengthFluxEstimator,
				   addPartialHistoryContribution,
				   ContributionMultiplierPolicy )
{
  typedef FACEMC::CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>
    CellTrackLengthFluxEstimator;

  Teuchos::RCP<CellTrackLengthFluxEstimator> estimator;
  initializeCellTrackLengthFluxEstimator<CellTrackLengthFluxEstimator>( 
								   estimator );

  FACEMC::PhotonState particle( 0ull );
  particle.setWeight( 1.0 );
  particle.setEnergy( 1.0 );

  estimator->addPartialHistoryContribution( particle, 0, 1.0 );

  particle.setEnergy( 0.5 );

  estimator->addPartialHistoryContribution( particle, 1, 1.0, 1 );

  estimator->commitHistoryContribution();

  FACEMC::Estimator::setNumberOfHistories( 1.0 );
  FACEMC::Estimator::setEndTime( 1.0 );

  std::cout << std::endl << *estimator << std::endl;
}

UNIT_TEST_INSTANTIATION( CellTrackLengthFluxEstimator, 
			 addPartialHistoryContribution );

//---------------------------------------------------------------------------//
// end tstCellTrackLengthFluxEstimator.cpp
//---------------------------------------------------------------------------//