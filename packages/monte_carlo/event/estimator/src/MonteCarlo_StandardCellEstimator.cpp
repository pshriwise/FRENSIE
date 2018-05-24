//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCellEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard cell estimator class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardCellEstimator.hpp"
#include "MonteCarlo_EstimatorHDF5FileHandler.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

// Assign discretization to an estimator dimension
/*! \details The MonteCarlo::OBSERVER_COSINE_DIMENSION cannot be discretized in
 * standard cell estimators.
 */
void StandardCellEstimator::assignDiscretization(
                        const Estimator::DimensionDiscretizationPointer& bins )
{
  if( bins->getDimension() == OBSERVER_COSINE_DIMENSION )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                bin_boundaries->getDimensionName() <<
                                " bins cannot be set for standard cell "
                                "estimators. The bins requested for standard "
                                "cell estimator " << this->getId() <<
                                " will be ignored!" );
  }
  else
    BaseEstimatorType::assignDiscretization( bin_boundaries );
}

// Assign the particle type to the estimator
/*! \details Photons, electrons and neutrons (or their adjoint
 * couterparts) can contribute to the estimator. Combinations are not
 * allowed.
 */
void StandardCellEstimator::assignParticleType(
                                            const ParticleType& particle_type )
{
  if( this->getNumberOfAssignedParticleTypes() != 0 )
  {
    FRENSIE_LOG_TAGGED_WARNING( "Estimator",
                                "Standard cell estimators can only have one "
                                "particle type contribute. Since estimator "
                                << this->getId() << " already has a particle "
                                "type assigned the requested particle type of "
                                << particle_type << " will be ignored!" );
  }
  else
    Estimator::assignParticleType( particle_types);
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCellEstimator.cpp
//---------------------------------------------------------------------------//
