//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.hpp
//! \author Luke Kersting
//! \brief  The electron scattering distribution ACE factory helpers declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HELPERS_HPP
#define MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HELPERS_HPP

// FRENSIE Includes
#include "Data_XSSEPRDataExtractor.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a cutoff elastic distribution
std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double cutoff_angle_cosine = 1.0 );

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a simple dipole bremsstrahlung distribution
std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data );

//! Create a detailed 2BS bremsstrahlung distribution
std::shared_ptr<const MonteCarlo::BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const int atomic_number );

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const unsigned subshell );

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create a atomic excitation distribution
std::shared_ptr<const MonteCarlo::AtomicExcitationElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistributionACEFactoryHelpers.hpp
//---------------------------------------------------------------------------//
