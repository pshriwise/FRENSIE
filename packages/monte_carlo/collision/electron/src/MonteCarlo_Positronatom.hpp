//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Positronatom.hpp
//! \author Luke Kersting
//! \brief  The positron-atom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_HPP
#define MONTE_CARLO_POSITRONATOM_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReactionType.hpp"
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_PositronatomCore.hpp"
#include "MonteCarlo_Atom.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The atom class for positron-atomic reactions
class Positronatom : public Atom<PositronatomCore>
{

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The reaction enum type
  typedef PositronatomicReactionType ReactionEnumType;

  //! The particle state type
  typedef PositronState ParticleStateType;

  //! Typedef for the reaction map
  typedef PositronatomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef PositronatomCore::ConstReactionMap ConstReactionMap;

  //! Return the reactions that are treated as scattering
  static const boost::unordered_set<PositronatomicReactionType>&
  getScatteringReactionTypes();

  //! Constructor
  template<typename InterpPolicy>
  Positronatom(
    const std::string& name,
    const unsigned atomic_number,
    const double atomic_weight,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const ConstReactionMap& standard_scattering_reactions,
    const ConstReactionMap& standard_absorption_reactions,
    const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
    const bool processed_cross_sections,
    const InterpPolicy policy );

  //! Constructor (from a core)
  Positronatom( const std::string& name,
                const unsigned atomic_number,
                const double atomic_weight,
                const PositronatomCore& core )
    : Atom<PositronatomCore>( name, atomic_number, atomic_weight, core )
  { /* ... */ }

  //! Destructor
  virtual ~Positronatom()
  { /* ... */ }

  //! Relax the atom
  void relaxAtom( const Data::SubshellType vacancy_shell,
                  const PositronState& positron,
                  ParticleBank& bank ) const;

  //! Return the cross section for a specific positron-atomic reaction
  double getReactionCrossSection(
                    const double energy,
                    const PositronatomicReactionType reaction ) const;

};

// Relax the atom
inline void Positronatom::relaxAtom( const Data::SubshellType vacancy_shell,
                                     const PositronState& positron,
                                     ParticleBank& bank ) const
{
  // Relax the atom
  this->getCore().getAtomicRelaxationModel().relaxAtom( vacancy_shell,
                                                        positron,
                                                        bank );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_Positronatom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_POSITRONATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Positronatom.hpp
//---------------------------------------------------------------------------//

