//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The bremsstrahlung Positronatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The bremsstrahlung positron-atomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class BremsstrahlungPositronatomicReaction : public StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
{
  // Typedef for the base class type
  typedef StandardReactionBaseImpl<PositronatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  BremsstrahlungPositronatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
              bremsstrahlung_distribution );

  //! Constructor
  BremsstrahlungPositronatomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>&
              bremsstrahlung_distribution );

  //! Destructor
  virtual ~BremsstrahlungPositronatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const override;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const override;

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const override;

  //! Return the differential cross section
  double getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const override;

  //! Simulate the reaction
  void react( PositronState& positron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const override;

private:

  // The bremsstrahlung scattering distribution
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    d_bremsstrahlung_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_BremsstrahlungPositronatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
