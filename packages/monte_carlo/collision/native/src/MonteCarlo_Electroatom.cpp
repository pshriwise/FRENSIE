//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Electroatom.cpp
//! \author Luke Kersting
//! \brief  The electroatom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Return the reactions that are treated as scattering
const boost::unordered_set<ElectroatomicReactionType>&
Electroatom::getScatteringReactionTypes()
{
  return ElectroatomCore::scattering_reaction_types;
}

// Return the cross section for a specific electroatomic reaction
double Electroatom::getReactionCrossSection(
                    const double energy,
                    const ElectroatomicReactionType reaction ) const
{
  switch( reaction )
  {
  case TOTAL_ELECTROATOMIC_REACTION:
    return this->getTotalCrossSection( energy );
  case TOTAL_ABSORPTION_ELECTROATOMIC_REACTION:
    return this->getAbsorptionCrossSection( energy );
  default:
    ConstReactionMap::const_iterator electroatomic_reaction =
      d_core.getScatteringReactions().find( reaction );

    if( electroatomic_reaction != d_core.getScatteringReactions().end() )
      return electroatomic_reaction->second->getCrossSection( energy );

    electroatomic_reaction = d_core.getAbsorptionReactions().find( reaction );

    if( electroatomic_reaction != d_core.getAbsorptionReactions().end() )
      return electroatomic_reaction->second->getCrossSection( energy );

    electroatomic_reaction = d_core.getMiscReactions().find( reaction );

    if( electroatomic_reaction != d_core.getMiscReactions().end() )
      return electroatomic_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for an atom, return 0
      return 0.0;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Electroatom.cpp
//---------------------------------------------------------------------------//


