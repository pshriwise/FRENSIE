//---------------------------------------------------------------------------//
//!
//! \file   SortingAlgorithms_def.hpp
//! \author Alex Robinson
//! \brief  Sorting algorithms definitions.
//!
//---------------------------------------------------------------------------//

#ifndef SORTING_ALGORITHMS_DEF_HPP
#define SORTING_ALGORITHMS_DEF_HPP

// FACEMC Includes
#include "TupleMemberTraits.hpp"
#include "ContractException.hpp"

namespace FACEMC{

namespace Sort{

// Test if the specified member of an array of tuples is sorted in ascending o.
/*! \details This function is nominally the same as the function in algorithms
 * of the new C++ 2011 standard library. When the transition to the 2011
 * standard is made, this function should be removed. The time complexity is 
 * linear in the number of elements in the container.
 */
template<TupleMember member, typename Iterator>
bool isSortedAscending( Iterator start, Iterator end )
{
  // Make sure the container is not empty
  testPrecondition( start != end );
  
  Iterator element_a = start;
  Iterator element_b = element_a;
  ++element_b;

  bool is_sorted = true;

  while( element_b != end )
  {
    if( get<member>( *element_a ) > get<member>( *element_b ) )
    {
      is_sorted = false;
      break;
    }
  }
  
  return is_sorted;
}

// Test if an array is sorted in ascending order
template<typename Iterator>
inline bool isSortedAscending( Iterator start, Iterator end )
{
  return isSortedAscending<FIRST>( start, end );
}

} // end Sort namespace

} // end FACEMC namespace

#endif // end SORTING_ALGORITHMS_DEF_HPP

//---------------------------------------------------------------------------//
// SortingAlgorithms_def.hpp
//---------------------------------------------------------------------------//