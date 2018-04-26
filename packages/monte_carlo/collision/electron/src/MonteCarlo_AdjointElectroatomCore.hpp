//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomCore.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP

// Std Lib Includes
#include <unordered_map>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! The adjoint electroatom core class for storing adjoint electroatomic reactions
 * \details This class can be used to store all reactions and the atomic
 * relaxation model associated with a adjoint electroatom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to
 * the underlying member data in a way that prohibits modification of that
 * data. This class was created to address the issue that arises when dealing
 * with electro-nuclear data - electro-nuclide's that share the same atomic number
 * need the same adjoint electroatomic data. This class allows each electro-nuclide to
 * share the adjoint electroatomic data without copying that data (even if each
 * electro-nuclide has its own copy of the adjoint electroatom core object).
 */
class AdjointElectroatomCore
{

public:

  //! Typedef for the particle state type
  typedef AdjointElectronState ParticleStateType;

  //! Typedef for the reaction map
  typedef boost::unordered_map<AdjointElectroatomicReactionType,
                               std::shared_ptr<AdjointElectroatomicReaction> >
  ReactionMap;

  //! Typedef for the const reaction map
  typedef boost::unordered_map<AdjointElectroatomicReactionType,
                           std::shared_ptr<const AdjointElectroatomicReaction> >
  ConstReactionMap;

  //! Default constructor
  AdjointElectroatomCore();

  //! Constructor
  AdjointElectroatomCore(
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
      const ConstReactionMap& scattering_reactions,
      const ConstReactionMap& absorption_reactions );

  //! Copy constructor
  AdjointElectroatomCore( const AdjointElectroatomCore& instance );

  //! Assignment operator
  AdjointElectroatomCore& operator=( const AdjointElectroatomCore& instance );

  //! Destructor
  ~AdjointElectroatomCore()
  { /* ... */ }

  //! Return the total forward reaction
  const ElectroatomicReaction& getTotalForwardReaction() const;

  //! Return the scattering reactions
  const ConstReactionMap& getScatteringReactions() const;

  //! Return the absorption reactions
  const ConstReactionMap& getAbsorptionReactions() const;

  //! Return the hash-based grid searcher
  const Utility::HashBasedGridSearcher<double>& getGridSearcher() const;

  //! Test if all of the reactions share a common energy grid
  bool hasSharedEnergyGrid() const;

private:

  // The total forward reactions
  std::shared_ptr<const ElectroatomicReaction> d_total_forward_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // The hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double>> d_grid_searcher;
};

// Return the total forward reaction
inline auto AdjointElectroatomCore::getTotalForwardReaction() const -> const ElectroatomicReaction&
{
  return *d_total_forward_reaction;
}

// Return the scattering reactions
inline auto AdjointElectroatomCore::getScatteringReactions() const -> const ConstReactionMap&
{
  return d_scattering_reactions;
}

// Return the absorption reactions
inline auto AdjointElectroatomCore::getAbsorptionReactions() const -> const ConstReactionMap&
{
  return d_absorption_reactions;
}

// Return the hash-based grid searcher
inline const Utility::HashBasedGridSearcher<double>& AdjointElectroatomCore::getGridSearcher() const
{
  return *d_grid_searcher;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomCore.hpp
//---------------------------------------------------------------------------//

