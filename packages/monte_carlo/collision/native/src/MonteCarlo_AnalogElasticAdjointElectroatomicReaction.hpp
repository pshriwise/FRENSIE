//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticAdjointElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The analog scattering elastic adjoint electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! The analog elastic adjoint electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class AnalogElasticAdjointElectroatomicReaction : public StandardGenericAtomicReaction<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef StandardGenericAtomicReaction<AdjointElectroatomicReaction,InterpPolicy,processed_cross_section>
    BaseType;

public:

  //! Basic Constructor
  AnalogElasticAdjointElectroatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
            scattering_distribution );

  //! Constructor
  AnalogElasticAdjointElectroatomicReaction(
      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
      const Teuchos::ArrayRCP<const double>& cross_section,
      const unsigned threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
            scattering_distribution );


  //! Destructor
  ~AnalogElasticAdjointElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  AdjointElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( AdjointElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

private:

  // The analog elastic scattering distribution
  std::shared_ptr<const AnalogElasticElectronScatteringDistribution>
    d_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AnalogElasticAdjointElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticAdjointElectroatomicReaction.hpp
//---------------------------------------------------------------------------//