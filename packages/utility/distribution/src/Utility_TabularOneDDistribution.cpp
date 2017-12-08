//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularOneDDistribution.cpp
//! \author Alex Robinson
//! \brief  The tabular one-dimensional distribution template instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_DISTRIBUTION_INST( UnitAwareTabularOneDDistribution<void,void> );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_WattDistribution.cpp
//---------------------------------------------------------------------------//
