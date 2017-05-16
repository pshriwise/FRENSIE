//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction native factory helpers definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC REACTIONS****
//----------------------------------------------------------------------------//

//! Create an analog elastic scattering electroatomic reaction
std::shared_ptr<ElectroatomicReaction>
createAnalogElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const bool linlinlog_interpolation_mode_on,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                      raw_electroatom_data.getElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<MonteCarlo::ElectroatomicReaction> reaction;

  if ( linlinlog_interpolation_mode_on )
  {
    ElectroatomicReactionNativeFactory::createAnalogElasticReaction<Utility::LinLinLog>(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else
  {
    ElectroatomicReactionNativeFactory::createAnalogElasticReaction<Utility::LinLinLin>(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  return reaction;
}

////! Create a hybrid elastic scattering electroatomic reaction
//std::shared_ptr<const ElectroatomicReaction>
//createHybridElasticReaction(
//    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
//    const double cutoff_angle_cosine,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on,
//    const double evaluation_tol )
//{
//  // Extract the common energy grid
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
//                      raw_electroatom_data.getElectronEnergyGrid().end() );

//  // Construct the hash-based grid searcher
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
//                              energy_grid,
//                              energy_grid.size()/10 ) );

//  // Create the reaction
//  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;

//  if ( linlinlog_interpolation_mode_on )
//  {
//    ElectroatomicReactionNativeFactory::createHybridElasticReaction<Utility::LinLinLog>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        cutoff_angle_cosine,
//        correlated_sampling_mode_on,
//        evaluation_tol );
//  }
//  else
//  {
//    ElectroatomicReactionNativeFactory::createHybridElasticReaction<Utility::LinLinLin>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        cutoff_angle_cosine,
//        correlated_sampling_mode_on,
//        evaluation_tol );
//  }
//  return reaction;
//}

////! Create an cutoff elastic scattering electroatomic reaction
//std::shared_ptr<const ElectroatomicReaction>
//createCutoffElasticReaction(
//    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
//    const Teuchos::ArrayRCP<const double>& energy_grid,
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const double cutoff_angle_cosine,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on,
//    const double evaluation_tol )
//{
//  // Extract the common energy grid
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
//                      raw_electroatom_data.getElectronEnergyGrid().end() );

//  // Construct the hash-based grid searcher
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
//                              energy_grid,
//                              energy_grid.size()/10 ) );

//  // Create the reaction
//  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;

//  if ( linlinlog_interpolation_mode_on )
//  {
//    ElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLog>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        cutoff_angle_cosine,
//        correlated_sampling_mode_on,
//        evaluation_tol );
//  }
//  else
//  {
//    ElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLin>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        cutoff_angle_cosine,
//        correlated_sampling_mode_on,
//        evaluation_tol );
//  }
//  return reaction;
//}

////! Create a screened Rutherford elastic scattering electroatomic reaction
//std::shared_ptr<const ElectroatomicReaction>
//createScreenedRutherfordElasticReaction(
//    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
//    const double cutoff_angle_cosine,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on,
//    const double evaluation_tol )
//{
//  // Extract the common energy grid
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
//                      raw_electroatom_data.getElectronEnergyGrid().end() );

//  // Construct the hash-based grid searcher
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
//                              energy_grid,
//                              energy_grid.size()/10 ) );

//  // Create the reaction
//  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;

//  if ( linlinlog_interpolation_mode_on )
//  {
//    ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction<Utility::LinLinLog>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        cutoff_angle_cosine,
//        correlated_sampling_mode_on,
//        evaluation_tol );
//  }
//  else
//  {
//    ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction<Utility::LinLinLin>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        cutoff_angle_cosine,
//        correlated_sampling_mode_on,
//        evaluation_tol );
//  }
//  return reaction;
//}

////! Create the moment preserving elastic scattering electroatomic reaction
//std::shared_ptr<const ElectroatomicReaction>
//createMomentPreservingElasticReaction(
//    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
//    const double cutoff_angle_cosine,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on,
//    const double evaluation_tol )
//{
//  // Extract the common energy grid
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
//                      raw_electroatom_data.getElectronEnergyGrid().end() );

//  // Construct the hash-based grid searcher
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
//                              energy_grid,
//                              energy_grid.size()/10 ) );

//  // Create the reaction
//  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;

//  if ( linlinlog_interpolation_mode_on )
//  {
//    ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LinLinLog>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        cutoff_angle_cosine,
//        correlated_sampling_mode_on,
//        evaluation_tol );
//  }
//  else
//  {
//    ElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LinLinLin>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        cutoff_angle_cosine,
//        correlated_sampling_mode_on,
//        evaluation_tol );
//  }
//  return reaction;
//}

////----------------------------------------------------------------------------//
////      ****ATOMIC EXCITATION DISTRIBUTION****
////----------------------------------------------------------------------------//

////! Create an atomic excitation scattering electroatomic reaction
//std::shared_ptr<const ElectroatomicReaction>
//createAtomicExcitationReaction(
//    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
//    const Teuchos::ArrayRCP<const double>& energy_grid,
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher )
//{
//  // Extract the common energy grid
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
//                      raw_electroatom_data.getElectronEnergyGrid().end() );

//  // Construct the hash-based grid searcher
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
//                              energy_grid,
//                              energy_grid.size()/10 ) );

//  // Create the reaction
//  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;

//  ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction );

//  return reaction;
//}

////----------------------------------------------------------------------------//
////      ****ELECTROIONIZATION SUBSHELL REACTIONS****
////----------------------------------------------------------------------------//

////! Create the subshell electroionization electroatomic reaction
//std::shared_ptr<const ElectroatomicReaction>
//createSubshellElectroionizationReaction(
//    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
//    const Teuchos::ArrayRCP<const double>& energy_grid,
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const unsigned subshell,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on,
//    const bool unit_based_interpolation_mode_on,
//    const double evaluation_tol )
//{
//  // Extract the common energy grid
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
//                      raw_electroatom_data.getElectronEnergyGrid().end() );

//  // Construct the hash-based grid searcher
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
//                              energy_grid,
//                              energy_grid.size()/10 ) );

//  // Create the reaction
//  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;

//  if ( linlinlog_interpolation_mode_on )
//  {
//    ElectroatomicReactionNativeFactory::createSubshellElectroionizationElasticReaction<MonteCarlo::ElectroatomicReaction,Utility::LinLinLog>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        correlated_sampling_mode_on,
//        unit_based_interpolation_mode_on,
//        evaluation_tol )
//  }
//  else
//  {
//    ElectroatomicReactionNativeFactory::createSubshellElectroionizationElasticReaction<MonteCarlo::ElectroatomicReaction,Utility::LinLinLin>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        correlated_sampling_mode_on,
//        unit_based_interpolation_mode_on,
//        evaluation_tol )
//  }
//  return reaction;
//}

////! Create the subshell electroionization electroatomic reactions
//std::vector<std::shared_ptr<const ElectroatomicReaction> >
//createSubshellElectroionizationReactions(
//    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on,
//    const bool unit_based_interpolation_mode_on,
//    const double evaluation_tol )
//{
//  // Extract the common energy grid
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
//                      raw_electroatom_data.getElectronEnergyGrid().end() );

//  // Construct the hash-based grid searcher
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
//                              energy_grid,
//                              energy_grid.size()/10 ) );

//  // Create the reaction
//  std::vector<std::shared_ptr<const ElectroatomicReaction> > reactions;

//  if ( linlinlog_interpolation_mode_on )
//  {
//    ElectroatomicReactionNativeFactory::createSubshellElectroionizationElasticReactions<MonteCarlo::ElectroatomicReaction,Utility::LinLinLog>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        correlated_sampling_mode_on,
//        unit_based_interpolation_mode_on,
//        evaluation_tol )
//  }
//  else
//  {
//    ElectroatomicReactionNativeFactory::createSubshellElectroionizationElasticReactions<MonteCarlo::ElectroatomicReaction,Utility::LinLinLin>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        correlated_sampling_mode_on,
//        unit_based_interpolation_mode_on,
//        evaluation_tol )
//  }
//  return reaction;
//}

////----------------------------------------------------------------------------//
////      ****BREMSSTRAHLUNG REACTIONS****
////----------------------------------------------------------------------------//

////! Create the bremsstrahlung electroatomic reaction
//std::shared_ptr<const ElectroatomicReaction>
//createBremsstrahlungReaction(
//    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
//    const bool dipole_distribution_mode_on,
//    const bool linlinlog_interpolation_mode_on,
//    const bool correlated_sampling_mode_on,
//    const bool unit_based_interpolation_mode_on,
//    const double evaluation_tol )
//{
//  // Extract the common energy grid
//  Teuchos::ArrayRCP<double> energy_grid;
//  energy_grid.assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
//                      raw_electroatom_data.getElectronEnergyGrid().end() );

//  // Construct the hash-based grid searcher
//  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
//     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
//                              energy_grid,
//                              energy_grid.size()/10 ) );


//  BremsstrahlungAngularDistributionType photon_distribution_function;

//  if ( dipole_distribution_mode_on )
//  {
//    photon_distribution_function = MonteCarlo::DIPOLE;
//  }
//  else
//  {
//    photon_distribution_function = MonteCarlo::TWOBS;
//  }

//  // Create the reaction
//  std::shared_ptr<const MonteCarlo::ElectroatomicReaction> reaction;

//  if ( linlinlog_interpolation_mode_on )
//  {
//    ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<MonteCarlo::ElectroatomicReaction,Utility::LinLinLog>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        photon_distribution_function,
//        correlated_sampling_mode_on,
//        unit_based_interpolation_mode_on,
//        evaluation_tol )
//  }
//  else
//  {
//    ElectroatomicReactionNativeFactory::createBremsstrahlungReaction<MonteCarlo::ElectroatomicReaction,Utility::LinLinLin>(
//        raw_electroatom_data,
//        energy_grid,
//        grid_searcher,
//        reaction,
//        photon_distribution_function,
//        correlated_sampling_mode_on,
//        unit_based_interpolation_mode_on,
//        evaluation_tol )
//  }
//  return reaction;
//}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//
