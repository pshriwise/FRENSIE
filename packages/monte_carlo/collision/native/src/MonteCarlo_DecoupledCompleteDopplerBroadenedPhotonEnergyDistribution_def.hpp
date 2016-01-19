//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The decoupled complete Doppler broadened photon energy dist. def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_DECOUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details The Compton profile grids must be in me*c units (not atomic 
 * units). The Compton profiles must be in inverse me*c units (not inverse 
 * atomic units). Only half profiles should be provided (grid ranges from 0.0 
 * to 1.0).
 */
template<typename ComptonProfilePolicy>
DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution(
	       const Teuchos::Array<double>& endf_subshell_occupancies,
	       const Teuchos::Array<SubshellType>& endf_subshell_order,
	       const Teuchos::Array<double>& old_subshell_binding_energies,
	       const Teuchos::Array<double>& old_subshell_occupancies,
               const std::shared_ptr<const ComptonProfileSubshellConverter>&
               subshell_converter,
	       const ElectronMomentumDistArray& electron_momentum_dist_array )
  : CompleteDopplerBroadenedPhotonEnergyDistribution(
                                                endf_subshell_occupancies,
                                                endf_subshell_order,
                                                subshell_converter,
                                                electron_momentum_dist_array ),
    d_old_subshell_occupancy_distribution(),
    d_old_subshell_binding_energy( old_subshell_binding_energies ),
    d_old_subshell_occupancies( old_subshell_occupancies ),
{
  // Make sure the old shell data is valid
  testPrecondition( old_subshell_binding_energies.size() > 0 );
  testPrecondition( old_subshell_occupancies.size() ==
		    old_subshell_binding_energies.size() );
  // Make sure the comptron profile array is valid
  testPrecondition( electron_momentum_dist_array.size() ==
		    old_subshell_binding_energies.size() );

  // Create the old subshell interaction distribution
  Teuchos::Array<double> dummy_indep_vals( old_subshell_occupancies.size() );

  d_old_subshell_occupancy_distribution.reset(
	       new Utility::DiscreteDistribution( dummy_indep_vals,
					          old_subshell_occupancies ) );
}

// Return the binding energy of a subshell
template<typename ComptonProfilePolicy>
double DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshellBindingEnergy( 
                                            const SubshellType subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  unsigned old_subshell_index = this->getOldSubshellIndex( subshell );

  return d_old_subshell_binding_energy[old_subshell_index];
}
  
// Return the occupancy of a subshell (default is the ENDF occupacy)
template<typename ComptonProfilePolicy>
double DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::getSubshellOccupancy( 
                                            const SubshellType subshell ) const
{
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  unsigned old_subshell_index = this->getOldSubshellIndex( subshell );

  return d_old_subshell_occupancies[old_subshell_index];
}

// Sample an interaction subshell
/*! \details The old subshell index used to select the Compton profile and
 * and the binding energy is not the same as the subshell (each are sampled
 * separately - i.e. they are decoupled).
 */
template<typename ComptonProfilePolicy>
void DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleInteractionSubshell( 
                                               unsigned& old_subshell_index,
                                               double& subshell_binding_energy,
                                               Subshell& subshell ) const
{
  old_subshell_index = this->sampleOldInteractionSubshell();

  subshell_binding_energy = d_old_subshell_binding_energy[old_subshell_index];

  subshell = this->sampleENDFInteractionSubshell();
}

// Sample the old subshell that is interacted with
template<typename ComptonProfilePolicy>
unsigned DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution<ComptonProfilePolicy>::sampleOldInteractionSubshell() const
{
  unsigned old_subshell_of_interaction;
  
  d_old_subshell_occupancy_distribution->sampleAndRecordBinIndex( 
						    old_shell_of_interaction );

  return old_subshell_of_interaction;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledCompleteDopplerBroadenedPhotonEnergyDistribution_def.hpp
//---------------------------------------------------------------------------//
