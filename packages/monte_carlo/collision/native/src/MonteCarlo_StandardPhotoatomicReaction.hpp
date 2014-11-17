//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The standard photoatomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"

namespace MonteCarlo{

/*! The standard photoatomic reaction base class
 * \details Use the InterpPolicy template parameter and the
 * processed_cross_section template parameter to customize the behavior of
 * this class. Raw cross section data from the EPDL library would use
 * a LogLog policy with processed_cross_section = false. Processed cross
 * section data from an ACE library would use a LogLog policy with
 * processed_cross_section = true. When data is processed, the policy is used
 * to indicate how the data was processed.
 */
template<typename InterpPolicy, bool processed_cross_section>
class StandardPhotoatomicReaction : public PhotoatomicReaction
{

public:

  //! Constructor
  StandardPhotoatomicReaction( 
		  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		  const Teuchos::ArrayRCP<const double>& cross_section,
		  const unsigned threshold_energy_index );

  //! Destructor
  virtual ~StandardPhotoatomicReaction()
  { /* ... */ }

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

private:

  // The processed incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The processed cross section values evaluated on the incoming e. grid 
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The threshold energy
  unsigned d_threshold_energy_index;
};

//! Partial template specialization for raw data
template<typename InterpPolicy>
class StandardPhotoatomicReaction<InterpPolicy,false> : public PhotoatomicReaction
{
  public:

  //! Constructor
  StandardPhotoatomicReaction( 
		  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		  const Teuchos::ArrayRCP<const double>& cross_section,
		  const unsigned threshold_energy_index );

  //! Destructor
  virtual ~StandardPhotoatomicReaction()
  { /* ... */ }

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

private:

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The threshold energy
  const unsigned d_threshold_energy_index;
};


} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//