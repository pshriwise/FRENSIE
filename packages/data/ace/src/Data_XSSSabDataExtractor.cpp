//---------------------------------------------------------------------------//
//!
//! \file   Data_XSSSabDataExtractor.cpp
//! \author Alex Robinson
//! \brief  XSS array (from ace table) S(a,b) data extractor class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_XSSSabDataExtractor.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace Data{

// Constructor
/*! \details A copy of the jxs array will be made so that is can be modified.
 * All indices in the jxs array correspond to a starting index of 1 (1 is
 * subtracted from all indices so that the correct array location is accessed).
 */
XSSSabDataExtractor::XSSSabDataExtractor(
                       const Utility::ArrayView<const int>& nxs,
                       const Utility::ArrayView<const int>& jxs,
		       const std::shared_ptr<const std::vector<double> >& xss )
  : d_nxs( nxs.begin(), nxs.end() ),
    d_jxs( jxs.begin(), jxs.end() ),
    d_xss( xss ),
    d_xss_view(),
    d_itie_block(),
    d_itce_block()
{
  // Make sure that the xss array exists
  testPrecondition( xss.get() );
  
  // Make sure the arrays have the correct size
  TEST_FOR_EXCEPTION( nxs.size() != 16,
                      std::runtime_error,
                      "Invalid nxs array encountered!" );

  TEST_FOR_EXCEPTION( jxs.size() != 32,
                      std::runtime_error,
                      "Invalid jxs array encountered!" );

  TEST_FOR_EXCEPTION( xss->size() != nxs[0],
                      std::runtime_error,
                      "The nxs array expected the xss array to have size "
                      << nxs[0] << " but it was found to have size "
                      << xss->size() << "!" );

  // Adjust the indices in the JXS array so that they correspond to a C-array
  for( size_t i = 0; i < d_jxs.size(); ++i )
    d_jxs[i] -= 1;

  // Create the XSS view
  d_xss_view = Utility::arrayViewOfConst( *d_xss );

  // Extract and cache the ITIE block and the ITCE block
  d_itie_block = d_xss_view( d_jxs[0], (int)d_xss_view[d_jxs[0]]*2 + 1 );

  // Extract and cache the ITCE block
  if( d_jxs[3] != -1 )
    d_itce_block = d_xss_view( d_jxs[3], (int)d_xss_view[d_jxs[3]]*2 + 1 );
}

// Return the inelastic scattering mode
SabInelasticMode XSSSabDataExtractor::getInelasticScatteringMode() const
{
  try{
    return convertUnsignedToSabInelasticMode( d_nxs[1] );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: invalid inelastic scattering mode found "
			   "while parsing nxs array.\n" );
}

// Return if elastic scattering cross section data is present
/*! \details Elastic scattering cross section data is only present if
 * jxs[3] != -1
 */
bool XSSSabDataExtractor::hasElasticScatteringCrossSectionData() const
{
  return d_jxs[3] != -1;
}

// Return if elastic scattering angular distribution is present
/*! \details Elastic scattering cross section data is only present if
 * jxs[3] != -1 and nxs[5] != -1
 */
bool XSSSabDataExtractor::hasElasticScatteringAngularDistributionData() const
{
  return d_jxs[3] != -1 && d_nxs[5] != -1;
}

// Return the elastic scattering mode
SabElasticMode XSSSabDataExtractor::getElasticScatteringMode() const
{
  return convertUnsignedToSabElasticMode( d_nxs[4] );
}

// Extract the ITIE block from the XSS array
Utility::ArrayView<const double> XSSSabDataExtractor::extractITIEBlock() const
{
  return d_itie_block;
}

// Extract the inelastic energy grid from the XSS array
Utility::ArrayView<const double> XSSSabDataExtractor::extractInelasticEnergyGrid() const
{
  return d_itie_block( 1, (int)d_itie_block[0] );
}

// Extract the inelastic energy grid from the XSS array
auto XSSSabDataExtractor::extractInelasticEnergyGridInMeV() const -> Utility::ArrayView<const Energy>
{
  return Utility::ArrayView<const Energy>(
               Utility::reinterpretAsQuantity<Energy>( d_itie_block.data()+1 ),
               Utility::ArrayView<const Energy>::size_type(d_itie_block[0]) );
}

// Extract the inelastic cross section from the XSS array
Utility::ArrayView<const double> XSSSabDataExtractor::extractInelasticCrossSection() const
{
  return d_itie_block( 1 + (int)d_itie_block[0], (int)d_itie_block[0] );
}

// Extract the inelastic cross section from the XSS array
auto XSSSabDataExtractor::extractInelasticCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  return Utility::ArrayView<const Area>(
           Utility::reinterpretAsQuantity<Area>(d_itie_block.data()+1+(int)d_itie_block[0]),
           Utility::ArrayView<const Area>::size_type(d_itie_block[0]) );
}

// Extract the ITCE block from the XSS array
Utility::ArrayView<const double>
XSSSabDataExtractor::extractITCEBlock() const
{
  return d_itce_block;
}

// Extract the elastic energy grid from the XSS array
Utility::ArrayView<const double> XSSSabDataExtractor::extractElasticEnergyGrid() const
{
  if( this->hasElasticScatteringCrossSectionData() )
    return d_itce_block( 1, (int)d_itce_block[0] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the elastic energy grid from the XSS array
auto XSSSabDataExtractor::extractElasticEnergyGridInMeV() const -> Utility::ArrayView<const Energy>
{
  if( this->hasElasticScatteringCrossSectionData() )
  {
    return Utility::ArrayView<const Energy>(
               Utility::reinterpretAsQuantity<Energy>( d_itce_block.data()+1 ),
               Utility::ArrayView<const Energy>::size_type(d_itce_block[0]) );
  }
  else
    return Utility::ArrayView<const Energy>();
}

// Extract the elastic cross section from the XSS array
Utility::ArrayView<const double> XSSSabDataExtractor::extractElasticCrossSection() const
{
  if( this->hasElasticScatteringCrossSectionData() )
    return d_itce_block( 1 + (int)d_itce_block[0], (int)d_itce_block[0] );
  else
    return Utility::ArrayView<const double>();
}

// Extract the elastic cross section from the XSS array
auto XSSSabDataExtractor::extractElasticCrossSectionInBarns() const -> Utility::ArrayView<const Area>
{
  if( this->hasElasticScatteringCrossSectionData() )
  {
    return Utility::ArrayView<const Area>(
            Utility::reinterpretAsQuantity<Area>(d_itce_block.data()+1+(int)d_itce_block[0]),
            Utility::ArrayView<const Area>::size_type(d_itce_block[0]) );
  }
  else
    return Utility::ArrayView<const Area>();
}

// Extract the ITXE block from the XSS array
Utility::ArrayView<const double>
XSSSabDataExtractor::extractITXEBlock() const
{
  if( hasElasticScatteringCrossSectionData() )
    return d_xss_view( d_jxs[2], d_jxs[3] - d_jxs[2] );
  else
    return d_xss_view( d_jxs[2], d_nxs[0] - d_jxs[2] );
}

// Extract the ITCA block from the XSS array
Utility::ArrayView<const double>
XSSSabDataExtractor::extractITCABlock() const
{
  if( hasElasticScatteringAngularDistributionData() )
    return d_xss_view( d_jxs[5], d_nxs[0] - d_jxs[5] );
  else
    return Utility::ArrayView<const double>();
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_XSSSabDataExtractor.cpp
//---------------------------------------------------------------------------//
