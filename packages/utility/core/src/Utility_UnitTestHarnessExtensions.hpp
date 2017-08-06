//---------------------------------------------------------------------------//
//!
//! \file   Utility_UnitTestHarnessExtensions.hpp
//! \author Alex Robinson
//! \brief  Extentions to the Teuchos_UnitTestHarness
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIT_TEST_HARNESS_EXTENSIONS_HPP
#define UTILITY_UNIT_TEST_HARNESS_EXTENSIONS_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_FancyOStream.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHelpers.hpp"
#include "Utility_TeuchosUnitTestInitializer.hpp"

/*! \defgroup unit_test_harness_extensions Teuchos Unit Test Harness Extensions
 * \ingroup testing
 *
 * Several macros have been written that extend the functionality of the
 * Teuchos Unit Test Harness. This additional functionality allows some
 * objects commonly used by Utility to be tested more easily.
 */

/*! \brief A macro for starting the custom Teuchos unit test setup.
 * \details This macro must come before the 
 * UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS macro and the 
 * UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION macro calls.
 */
#define UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN() \
  class CustomTeuchosUnitTestInitializer : public Utility::TeuchosUnitTestInitializer \
  {                                                                     \
  public:                                                               \
    CustomTeuchosUnitTestInitializer()                                  \
    { Utility::TeuchosUnitTestInitializer::setInitializer( this ); }  \
    ~CustomTeuchosUnitTestInitializer()                               \
    { /* ... */ }                                                     \
  protected:                                                          \
    void __dummy__()

/*! \brief A macro for finishing the custom Teuchos unit test setup.
 * \details This macro must come after the 
 * UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS macro and the 
 * UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION macro calls.
 */
#define UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END()                    \
  };                                                                    \
  CustomTeuchosUnitTestInitializer* initializer_instance =              \
    new CustomTeuchosUnitTestInitializer

/*! \brief A macro for setting custom Teuchos command line options for
 * the unit tests. 
 * \details Variables that need to be access outside of this macro call
 * should be declared outside of the function block. If the only other place
 * where the variable is needed is in the function block of the
 * UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION macro, declare the
 * variable(s) inside of the 
 * UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN and
 * UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END macros to ensure that they
 * stay out of the global scope. To access the command line 
 * processor simply call "clp()".
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS() \
  void setCommandLineProcessorOptions() \

/*! \brief A macro for initializing custom unit test data. This macro can
 * be called before or after the
 * UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS. To promote clarity 
 * it is recommended that it be called after.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION() \
  void initialize() const \

/*! \brief A macro for the Teuchos Unit Test Harness for creating a
 * templated unit test on a Tuple Member and a type.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_DECL(TEST_GROUP, TEST_NAME, MEMBER, TUPLE) \
  template<size_t MEMBER, typename TUPLE>			\
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& memberName,					\
      const std::string& tupleName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP, std::string(#TEST_NAME)+"_"+memberName+"_"+tupleName ) \
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<size_t MEMBER, typename TUPLE>			\
  void TEST_GROUP##_##TEST_NAME##_UnitTest<MEMBER,TUPLE>::runUnitTestImpl( \
         Teuchos::FancyOStream &out, bool &success ) const \

/*! \brief A macro for the Teuchos Unit Test Harness for instantiating a
 * templated unit test on a Tuple Member and a type.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_1_TUPLE_1_TEMPLATE_INSTANT(TEST_GROUP, TEST_NAME, MEMBER, TUPLE) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER, TUPLE>; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER, TUPLE>		\
  instance_##TEST_GROUP##_##MEMBER##_##TUPLE##_##TEST_NAME##_UnitTest(#MEMBER,#TUPLE);

/*! \brief A macro for the Teuchos Unit Test Harness for creating a
 * templated unit test on two Tuple Member and a tuple type.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_DECL(TEST_GROUP, TEST_NAME, MEMBER1, MEMBER2, TUPLE) \
  template<size_t MEMBER1, size_t MEMBER2, typename TUPLE> \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& member1Name,					\
      const std::string& member2Name,					\
      const std::string& tupleName					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP, std::string(#TEST_NAME)+"_"+member1Name+"_"+member2Name+"_"+tupleName ) \
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
    template<size_t MEMBER1, size_t MEMBER2, typename TUPLE> \
    void TEST_GROUP##_##TEST_NAME##_UnitTest<MEMBER1,MEMBER2,TUPLE>::runUnitTestImpl( \
         Teuchos::FancyOStream &out, bool &success ) const \

/*! \brief A macro for the Teuchos Unit Test Harness for instantiating a
 * templated unit test on two Tuple Members and a tuple type.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_2_TUPLE_1_TEMPLATE_INSTANT(TEST_GROUP, TEST_NAME, MEMBER1, MEMBER2, TUPLE) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER1, Utility::MEMBER2, TUPLE>; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER1, Utility::MEMBER2, TUPLE> \
  instance_##TEST_GROUP##_##MEMBER1##_##MEMBER2##_##TUPLE##_##TEST_NAME##_UnitTest(#MEMBER1,#MEMBER2,#TUPLE);

/*! \brief A macro for the Teuchos Unit Test Harness for creating a
 * templated unit test on two Tuple Members and two tuple types.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_DECL(TEST_GROUP, TEST_NAME, MEMBER1, MEMBER2, TUPLE1, TUPLE2) \
  template<size_t MEMBER1,				\
	   size_t MEMBER2,				\
	   typename TUPLE1,						\
	   typename TUPLE2>						\
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest(				\
      const std::string& member1Name,					\
      const std::string& member2Name,					\
      const std::string& tuple1Name,					\
      const std::string& tuple2Name					\
    )                                                                   \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP,				                        \
	std::string(#TEST_NAME)+"_"+member1Name+"_"+tuple1Name+		\
	"_"+member2Name+"_"+tuple2Name )				\
    {}									\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };									\
									\
  template<size_t MEMBER1,				\
	   size_t MEMBER2,				\
	   typename TUPLE1,						\
	   typename TUPLE2>						\
  void TEST_GROUP##_##TEST_NAME##_UnitTest<MEMBER1,MEMBER2,TUPLE1,TUPLE2>::runUnitTestImpl( \
         Teuchos::FancyOStream &out, bool &success ) const \

/*! \brief A macro for the Teuchos Unit Test Harness for instantiating a
 * templated unit test on two Tuple Member and two tuple types.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_MEMBER_2_TUPLE_2_TEMPLATE_INSTANT(TEST_GROUP, TEST_NAME, MEMBER1, MEMBER2, TUPLE1, TUPLE2 ) \
  template class TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER1, Utility::MEMBER2, TUPLE1, TUPLE2>; \
  TEST_GROUP##_##TEST_NAME##_UnitTest<Utility::MEMBER1, Utility::MEMBER2, TUPLE1, TUPLE2> \
  instance_##TEST_GROUP##_##MEMBER1##_##TUPLE1##_##MEMBER2##_##TUPLE2##TEST_NAME##_UnitTest(#MEMBER1,#MEMBER2,#TUPLE1,#TUPLE2);

/*! \brief A macro for the Teuchos Unit Test Harness for creating a
 * templated unit test on an unsigned type.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_UNIT_TEST_UNSIGNED_TEMPLATE_1_DECL(TEST_GROUP, TEST_NAME, UNSIGNED_VALUE) \
  template<size_t UNSIGNED_VALUE> \
  class TEST_GROUP##_##TEST_NAME##_UnitTest : public Teuchos::UnitTestBase \
  {									\
  public:								\
    TEST_GROUP##_##TEST_NAME##_UnitTest( const std::string& unsignedValue ) \
    : Teuchos::UnitTestBase(						\
	#TEST_GROUP, unsignedValue+"_"+std::string(#TEST_NAME) ) \
    {}								\
    void runUnitTestImpl( Teuchos::FancyOStream &out, bool &success ) const; \
    virtual std::string unitTestFile() const { return __FILE__; }	\
    virtual long int unitTestFileLineNumber() const { return __LINE__; } \
  };								       \
								       \
    template<size_t UNSIGNED_VALUE>				       \
    void TEST_GROUP##_##TEST_NAME##_UnitTest<UNSIGNED_VALUE>::runUnitTestImpl(\
			    Teuchos::FancyOStream &out, bool &success ) const \

/*! A macro for the Teuchos Unit Test Harness for comparing ordinal data types
 * and containers of ordinal data types.
 *
 * This macro allows tuples (Utility::Pair, Utility::Trip and Utility::Quad),
 * which are not supported by the standard Teuchos Unit Test Harness, to be
 * easily tested.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_TEST_EQUALITY( t1, t2 )					\
  {									\
    const bool result = Utility::compare(t1,#t1,t2,#t2,out,-1);		\
    (out) << TEUCHOS_PASS_FAIL(result) << "\n";				\
    if( !result ) success = false;					\
  }

/*! \brief A macro for the Teuchos Unit Test Harness for comparing floating
 * point data types and containers of floating point data types.
 *
 * This macro allows tuples (Utility::Pair, Utility::Trip and Utility::Quad),
 * which are not supported by the standard Teuchos Unit Test Harness, to be
 * easily tested.
 * \ingroup unit_test_harness_extensions
 */
#define UTILITY_TEST_FLOATING_EQUALITY( t1, t2, tol )			\
  {									\
    const bool result = Utility::compare(t1,#t1,t2,#t2,out,-1,tol);	\
    (out) << TEUCHOS_PASS_FAIL(result) << "\n";				\
    if( !result ) success = false;					\
  }

/*! A macro for the Teuchos Unit Test Harness for comparing containers.
 * \ingroup unit_test_harness_extensions
 */
#define TEST_COMPARE_CONTAINERS( c1, c2 )       \
  {                                                                     \
    const bool result = Utility::compareContainers( c1, #c1, c2, #c2, out ); \
    (out) << TEUCHOS_PASS_FAIL(result) << "\n\n";                       \
    if( !result ) success = false;                                      \
  }

/*! A macro for the Teuchos Unit Test Harness for comparing unordered containers.
 * \ingroup unit_test_harness_extensions
 */
#define TEST_COMPARE_UNORDERED_CONTAINERS( c1, c2 )       \
  {                                                                     \
    const bool result = Utility::compareUnorderedContainers( c1, #c1, c2, #c2, out ); \
    (out) << TEUCHOS_PASS_FAIL(result) << "\n\n";                       \
    if( !result ) success = false;                                      \
  }

/*! A macro for the Teuchos Unit Test Harness for comparing containers of 
 * floating point types
 * \ingroup unit_test_harness_extensions
 */
#define TEST_COMPARE_FLOATING_CONTAINERS( c1, c2, tol ) \
  {                                                     \
    const bool result = Utility::compareContainers( c1, #c1, c2, #c2, out, tol ); \
    (out) << TEUCHOS_PASS_FAIL(result) << "\n\n";                       \
    if( !result ) success = false;                                      \
  }


#endif // end UTILITY_UNIT_TEST_HARNESS_EXTENSIONS_HPP

//---------------------------------------------------------------------------//
// end Utility_UnitTestHarnessExtensions.hpp
//---------------------------------------------------------------------------//

