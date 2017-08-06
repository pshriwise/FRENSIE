//---------------------------------------------------------------------------//
//!
//! \file   Utility_ToStringTraits.hpp
//! \author Alex Robinson
//! \brief  ToStringTraits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TO_STRING_TRAITS_HPP
#define UTILITY_TO_STRING_TRAITS_HPP

// Std Lib Includes
#include <sstream>
#include <type_traits>
#include <iterator>
#include <stdexcept>

// FRENSIE Includes
#include "Utility_ToStringTraitsDecl.hpp"
#include "Utility_LogRecordType.hpp"

namespace Utility{

/*! Specialization of ToStringTraits for std::string
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<std::string>
{
  //! Return the string
  static inline std::string toString( const std::string& obj )
  { return obj; }

  //! Place the string in a stream
  static inline void toStream( std::ostream& os, const std::string& obj )
  { os << obj; }
};

/*! Specialization of ToStringTraits for const char*
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<const char*>
{
  //! Return the string
  static inline std::string toString( const char* obj )
  { return obj; }

  //! Place the c-string in a stream
  static inline void toStream( std::ostream& os, const char* obj )
  { os << obj; }
};

/*! Specialization of ToStringTraits for char*
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<char*> : public ToStringTraits<const char*>
{ /* ... */ };

/*! Partial specialization of ToStringTraits for char[]
 * \ingroup to_string_traits
 */
template<size_t N>
struct ToStringTraits<char[N]> : public ToStringTraits<const char*>
{ /* ... */ };

/*! Partial specialization of ToStringTraits for const char[]
 * \ingroup to_string_traits
 */
template<size_t N>
struct ToStringTraits<const char[N]> : public ToStringTraits<const char*>
{ /* ... */ };

/*! Specialization of ToStringTraits for Utility::LogRecordType
 *
 * This specialization is not specified with the LogRecordType enum because
 * of the potential for other ToStringTraits specializations to indirectly 
 * depend on the enum. Declaring this specialization here prevents any 
 * circular dependecies.
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<LogRecordType>
{
  //! Return the string
  static std::string toString( const LogRecordType obj );

  //! Place the LogRecordType in a stream
  static inline void toStream( std::ostream& os, const LogRecordType obj )
  { os << Utility::toString( obj ); }
};
  
/*! Specialization of ToStringTraits for bool
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<bool>
{
  //! Convert the boolean to a string
  static inline std::string toString( const bool& obj )
  { return (obj ? "true" : "false"); }

  //! Place the boolean in a stream
  static inline void toStream( std::ostream& os, const bool& obj )
  { os << ToStringTraits<bool>::toString( obj ); }
};

/*! Specialization of ToStringTraits for float
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<float>
{
  //! Convert the float to a string
  static inline std::string toString( const float& obj )
  {
    std::ostringstream oss;

    ToStringTraits<float>::toStream( oss, obj );
    
    return oss.str();
  }

  //! Place to float in a stream
  static inline void toStream( std::ostream& os, const float& obj )
  {
    // Make the stream precision high enough to capture the float without any
    // rounding loss
    os.setf( std::ios::scientific );
    os.precision( 9 );
    
    os << obj;
  }
};

/*! Specialization of ToStringTraits for double
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<double>
{
  //! Convert the double to a string
  static inline std::string toString( const double& obj )
  {
    std::ostringstream oss;

    ToStringTraits<double>::toStream( oss, obj );
    
    return oss.str();
  }

  //! Place the double in a stream
  static inline void toStream( std::ostream& os, const double& obj )
  {
    // Make the stream precision high enough to capture the double without any
    // rounding loss
    os.setf( std::ios::scientific );
    os.precision( 18 );
    
    os << obj;
  }
};

/*! Partial specialization of ToStringTraits for integral types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<T,typename std::enable_if<std::is_integral<T>::value>::type>
{
  //! Convert the integral type to a string
  static inline std::string toString( const T& obj )
  {
    std::ostringstream oss;

    ToStringTraits<T>::toStream( oss, obj );

    return oss.str();
  }

  //! Place the integral type in a stream
  static inline void toStream( std::ostream& os, const T& obj )
  { os << obj; }
};

/*! Partial specialization of ToStringTraits for std::exception types
 * \ingroup to_string_traits
 */
template<typename T>
struct ToStringTraits<T,typename std::enable_if<std::is_base_of<std::exception,T>::value>::type>
{
  //! Convert the std::exception type to a string
  static inline std::string toString( const std::exception& obj )
  { return obj.what(); }

  //! Place the std::exception type in a stream
  static inline void toStream( std::ostream& os, const std::exception& obj )
  { os << obj.what(); }
}

namespace Details{

//! ToStringTraits helper class for types with iterators
template<typename T>
struct ToStringTraitsIteratorHelper
{
  //! Convert the object of type T to a string
  static inline std::string toString( const T& obj )
  { 
    std::ostringstream oss;

    ToStringTraits<T>::toStream( oss, obj );

    return oss.str();
  }

  //! Place the object of type T in a stream
  static inline void toStream( std::ostream& os, const T& obj )
  {
    os << Utility::container_start_char;

    typename T::const_iterator it, end;
    it = obj.begin();
    end = obj.end();

    while( it != end )
    {
      Utility::toStream( os, *it );

      ++it;

      if( it != end )
        os << Utility::next_container_element_char << " ";
    }

    os << Utility::container_end_char;
  }
};
  
} // end Details namespace

// Convert the object to a string
template<typename T>
inline std::string toString( const T& obj )
{
  return Utility::ToStringTraits<T>::toString( obj );
}

// Place the object in a stream
template<typename T>
inline void toStream( std::ostream& os, const T& obj )
{
  Utility::ToStringTraits<T>::toStream( os, obj );
}

} // end Utility namespace

#endif // end UTILITY_TO_STRING_TRAITS_HPP

//---------------------------------------------------------------------------//
// end Utility_ToStringTraits.hpp
//---------------------------------------------------------------------------//
