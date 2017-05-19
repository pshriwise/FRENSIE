//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AbsorptionElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The absorption electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"

namespace MonteCarlo{

/*! The absorption electroatomic reaction
 * \details This reaction should be used to represent miscellaneous
 * absorption reactions (e.g. heating).
 */
template<typename InterpPolicy, bool processed_cross_section = false>
class AbsorptionElectroatomicReaction : public StandardGenericAtomicReaction<ElectroatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef StandardGenericAtomicReaction<ElectroatomicReaction,InterpPolicy,processed_cross_section> 
    BaseType;

public:

  //! Constructor
  AbsorptionElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const ElectroatomicReactionType reaction );

  //! Constructor
  AbsorptionElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const ElectroatomicReactionType reaction );

  //! Destructor
  ~AbsorptionElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const;

  //! Simulate the reaction
  void react( ElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

private:

  // The reaction type
  ElectroatomicReactionType d_reaction;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AbsorptionElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ABSORPTION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AbsorptionElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
