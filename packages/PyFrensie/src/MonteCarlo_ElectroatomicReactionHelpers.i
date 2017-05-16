//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionHelpers.i
//! \author Luke Kersting
//! \brief  The reaction helper macros
//!
//---------------------------------------------------------------------------//

%{
#include "PyFrensie_DistributionHelpers.hpp"
%}

// Include std::string support
%include <std_string.i>


// Import the PyFrensie utility
%import "PyFrensie_DistributionHelpers.hpp"

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic Electroatomic Reaction class python interface
//---------------------------------------------------------------------------//
%define %electroatomic_reaction_interface_setup( REACTION )

%feature("docstring") REACTION
"The REACTION proxy class. This class can getNumberOfEmittedElectrons,
getNumberOfEmittedPhotons, getCrossSection, getDifferentialCrossSection."

%feature("autodoc",
"getNumberOfEmittedElectrons(REACTION self, const double energy) -> unsigned" )
MonteCarlo::REACTION::getNumberOfEmittedElectrons;

%feature("autodoc",
"getNumberOfEmittedPhotons(REACTION self, const double energy) -> unsigned" )
MonteCarlo::REACTION::getNumberOfEmittedPhotons;

%feature("autodoc",
"getCrossSection(REACTION self, const double energy) -> double")
MonteCarlo::REACTION::getCrossSection;

%feature("autodoc",
"getDifferentialCrossSection(REACTION self) -> double" )
MonteCarlo::REACTION::getDifferentialCrossSection;

%enddef

//---------------------------------------------------------------------------//
// end Utility_ElectroatomicReactionHelpers.i
//---------------------------------------------------------------------------//
