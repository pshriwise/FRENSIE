//---------------------------------------------------------------------------//
//!
//! \file   tstLegendrePolynomial.cpp
//! \author Luke Kersting
//! \brief  Gauss-Radau quadrature kernel unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_LegendrePolynomial.hpp"

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the Legendre Polynomials can be evaluated
TEUCHOS_UNIT_TEST( LegendrePolynomial,
		           getLegendrePolynomial )
{
  double tol = 1e-12;
  double value = 0.5;
  int n = 0;
  double legendre_value = Utility::getLegendrePolynomial( value, n );

  TEST_EQUALITY_CONST( legendre_value, 1.0);

  n = 1;
  legendre_value = Utility::getLegendrePolynomial( value, n );

  TEST_EQUALITY_CONST( legendre_value, value);

  n = 4;
  legendre_value = Utility::getLegendrePolynomial( value, n );

  TEST_FLOATING_EQUALITY( legendre_value, -0.289062500000000, tol );

  n = 10;
  legendre_value = Utility::getLegendrePolynomial( value, n );

  TEST_FLOATING_EQUALITY( legendre_value, -0.188228607177734, tol );
}

//---------------------------------------------------------------------------//
// Check that the Legendre Polynomials derivatives can be evaluated
TEUCHOS_UNIT_TEST( LegendrePolynomial,
		           getLegendrePolynomialDerivative )
{
  double tol = 1e-12;
  double value = 0.5;
  int n = 0;
  double legendre_value = Utility::getLegendrePolynomialDerivative( value, n );

  TEST_EQUALITY_CONST( legendre_value, 0.0);

  n = 1;
  legendre_value = Utility::getLegendrePolynomialDerivative( value, n );

  TEST_EQUALITY_CONST( legendre_value, 1.0);

  n = 4;
  legendre_value = Utility::getLegendrePolynomialDerivative( value, n );

  TEST_FLOATING_EQUALITY( legendre_value, -1.562500000000000, tol );

  n = 10;
  legendre_value = Utility::getLegendrePolynomialDerivative( value, n );

  TEST_FLOATING_EQUALITY( legendre_value, -2.317123413085940, tol );
}

//---------------------------------------------------------------------------//
// end tstLegendrePolynomial.cpp
//---------------------------------------------------------------------------//
