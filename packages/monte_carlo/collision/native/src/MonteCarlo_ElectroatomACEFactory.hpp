//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomACEFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom ace factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The Electroatomic factory class that uses ACE data
class ElectroatomACEFactory
{

public:

  //! Create a electroatom core (using the provided atomic relaxation model)
  static void createElectroatomCore( 
	    const Data::XSSEPRDataExtractor& raw_electroatom_data,
        const double elastic_cutoff_angle,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<ElectroatomCore>& electroatom_core,
        const bool use_detailed_bremsstrahlung_data,
	    const bool use_atomic_relaxation_data );

  //! Create a electroatom (using the provided atomic relaxation model)
  static void createElectroatom(
	    const Data::XSSEPRDataExtractor& raw_electroatom_data,
	    const std::string& electroatom_name,
        const double elastic_cutoff_angle,
        const double atomic_weight,
	    const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	    Teuchos::RCP<Electroatom>& electroatom,
        const bool use_detailed_bremsstrahlung_data,
	    const bool use_atomic_relaxation_data );
private:

  // Constructor
  ElectroatomACEFactory();
};

} // end MonteCarlo

#endif // end MONTE_CARLO_ELECTROATOM_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomACEFactory.hpp
//---------------------------------------------------------------------------//
