//---------------------------------------------------------------------------//
// \file   SearchAlgorithms.hpp
// \author Alex Robinson
// \brief  Functions declarations for searching algorithms.
//---------------------------------------------------------------------------//

#ifndef SEARCH_ALGORITHMS_HPP
#define SEARCH_ALGORITHMS_HPP

// Std Lib Includes
#include <iterator>

// FACEMC Includes
#include "TupleComparePolicy.hpp"

namespace FACEMC{

namespace Search{

//! Binary search on an array of continuous data
template<TupleMember member, typename Iterator>
Iterator binarySearchContinuousData( Iterator start,
				     Iterator end,
				     const typename TupleComparePolicy<typename std::iterator_traits<Iterator>::value_type,member>::tupleMemberType value );

//! Binary search on an array of discrete data
template<TupleMember member, typename Iterator>
Iterator binarySearchDiscreteData( Iterator start,
				   Iterator end,
				   const typename TupleComparePolicy<typename std::iterator_traits<Iterator>::value_type,member>::tupleMemberType value);

} // end Search namespace

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "SearchAlgorithms_def.hpp"

//---------------------------------------------------------------------------//

#endif // end SEARCH_ALGORITHMS_HPP

//---------------------------------------------------------------------------//
// end SearchAlgorithms.hpp
//---------------------------------------------------------------------------//
