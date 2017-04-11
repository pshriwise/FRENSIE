//---------------------------------------------------------------------------//
//!
//! \file   Data_DataContainerHelpers_def.hpp
//! \author Luke Kersting
//! \brief  The data container helpers def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Test preconditions for energy grids
template<typename Array>
inline bool EnergyGridValid( const Array& energy_grid )
{
  return( energy_grid.size() > 1 &&
          Utility::Sort::isSortedAscending( energy_grid.begin(),
                                            energy_grid.end() ) &&
          energy_grid.front() > 0.0 );
}

// Test preconditions for values in array greater than zero
template<typename Array>
inline bool ValuesGreaterThanZero( const Array& values )
{
  return std::find_if( values.begin(),
                       values.end(),
                       isValueLessThanOrEqualToZero ) == values.end();
}

// Test preconditions for values in array greater than zero
template<typename Array>
inline bool ValuesGreaterThanOrEqualToZero( const Array& values )
{
  return std::find_if( values.begin(),
                       values.end(),
                       isValueLessThanZero ) == values.end();
}

// Test preconditions for values in array less than one
template<typename Array>
inline bool ValuesLessThanOne( const Array& values )
{
  return std::find_if( values.begin(),
                       values.end(),
                       isValueGreaterThanOrEqualToOne ) == values.end();
}

// Test preconditions for values in array less than one
template<typename Array>
inline bool ValuesLessThanOrEqualToOne( const Array& values )
{
  return std::find_if( values.begin(),
                       values.end(),
                       isValueGreaterThanOne ) == values.end();
}

// Test if a value is less than or equal to zero
bool isValueLessThanOrEqualToZero( const double value )
{
  return value <= 0.0;
}

// Test if a value is less than zero
bool isValueLessThanZero( const double value )
{
  return value < 0.0;
}

// Test if a value is greater than one
bool isValueGreaterThanOne( const double value )
{
  return value > 1.0;
}

// Test if a value is greater than or equal to one
bool isValueGreaterThanOrEqualToOne( const double value )
{
  return value >= 1.0;
}

// Test if a value is less than -1.0
bool isValueLessThanMinusOne( const double value )
{
  return value < -1.0;
}


} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_DataContainerHelpers.cpp
//---------------------------------------------------------------------------//
