//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Spatial distribution factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Includes
#include <map>

// FRENSIE Includes
#include "Utility_SpatialDistributionFactory.hpp"
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_CylindricalSpatialDistribution.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Utility{

// Create the spatial distribution represented by the parameter list
Teuchos::RCP<SpatialDistribution> 
SpatialDistributionFactory::createDistribution( 
			       const Teuchos::ParameterList& distribution_rep )
{
  // Validate the distribution representation
  SpatialDistributionFactory::validateDistributionRep( distribution_rep );
  
  // Create a cartesian spatial distribution
  if( distribution_rep.isParameter( "X Distribution" ) )
  {
    return SpatialDistributionFactory::createCartesianDistribution( 
							    distribution_rep );
  }
  
  // Create a cylindrical spatial distribution
  else if( distribution_rep.isParameter( "Axis Distribution" ) )
  {
    return SpatialDistributionFactory::createCylindricalDistribution(
							    distribution_rep );
  }

  // Create a spherical spatial distribution
  else if( distribution_rep.isParameter( "Mu Distribution" ) )
  {
    return SpatialDistributionFactory::createSphericalDistribution(
							    distribution_rep );
  }
}

// Validate the distribution representation
void SpatialDistributionFactory::validateDistributionRep( 
			       const Teuchos::ParameterList& distribution_rep )
{
  bool valid_distribution = false;
  
  // Make sure a valid cartesian distribution has been specified
  if( distribution_rep.isParameter( "X Distribution" ) )
  {
    TEST_FOR_EXCEPTION( distribution_rep.isParameter( "X Distribution" ) &&
			(!distribution_rep.isParameter( "Y Distribution" ) ||
			 !distribution_rep.isParameter( "Z Distribution" ) ),
			InvalidSpatialDistributionRepresentation,
			"Error: A cartesian spatial distribution needs to "
			"have the x, y, and z distributions specified!" );
    
    TEST_FOR_EXCEPTION( distribution_rep.numParams() != 3,
			InvalidSpatialDistributionRepresentation,
			"Error: Three 1D distributions must be specified for "
			"a cartesian spatial distribution!" );

    valid_distribution = true;
  }
  else if( distribution_rep.isParameter( "Y Distribution" ) )
  {
    TEST_FOR_EXCEPTION( distribution_rep.isParameter( "Y Distribution" ) &&
			(!distribution_rep.isParameter( "X Distribution" ) ||
			 !distribution_rep.isParameter( "Z Distribution" ) ),
			InvalidSpatialDistributionRepresentation,
			"Error: A cartesian spatial distribution needs to "
			"have the x, y, and z distributions specified!" );

    TEST_FOR_EXCEPTION( distribution_rep.numParams() != 3,
			InvalidSpatialDistributionRepresentation,
			"Error: Three 1D distributions must be specified for "
			"a cartesian spatial distribution!" );

    valid_distribution = true;
  }

  // Make sure a valid cylindrical distribution has been specified
  if( distribution_rep.isParameter( "Axis Distribution" ) )
  {
    TEST_FOR_EXCEPTION( distribution_rep.isParameter( "Axis Distribution" ) &&
			(!distribution_rep.isParameter( "R Distribution" ) ||
			 !distribution_rep.isParameter( "Theta Distribution")),
			InvalidSpatialDistributionRepresentation,
			"Error: A cylindrical spatial distribution needs to "
			"have the r, theta, and axis distribution specified!");

    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Center X Position" ) ||
			!distribution_rep.isParameter( "Center Y Position" ) ||
			!distribution_rep.isParameter( "Center Z Position" ),
			InvalidSpatialDistributionRepresentation,
			"Error: A cylindrical spatial distribution needs to "
			"have the center coordinate specified!" );

    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Axis" ),
			InvalidSpatialDistributionRepresentation,
			"Error: A cylindrical spatial distribution needs to "
			"have the alignment axis specified!" );

    TEST_FOR_EXCEPTION( distribution_rep.numParams() != 7,
			InvalidSpatialDistributionRepresentation,
			"Error: Three 1D distributions, the center "
			"coordinates and the axis must be specified for "
			"a cylindrical spatial distribution!" );

    valid_distribution = true;
  }

  // Make sure a valid spherical distribution has been specified
  if( distribution_rep.isParameter( "Mu Distribution" ) )
  {
    TEST_FOR_EXCEPTION( distribution_rep.isParameter( "Mu Distribution" ) &&
			(!distribution_rep.isParameter( "R Distribution" ) ||
			 !distribution_rep.isParameter( "Theta Distribution")),
			InvalidSpatialDistributionRepresentation,
			"Error: A spherical spatial distribution needs to "
			"have the r, theta, and mu distribution specified!");

    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Center X Position" ) ||
			!distribution_rep.isParameter( "Center Y Position" ) ||
			!distribution_rep.isParameter( "Center Z Position" ),
			InvalidSpatialDistributionRepresentation,
			"Error: A spherical spatial distribution needs to "
			"have the center coordinate specified!" );

    TEST_FOR_EXCEPTION( !distribution_rep.isParameter( "Axis" ),
			InvalidSpatialDistributionRepresentation,
			"Error: A spherical spatial distribution needs to "
			"have the alignment axis specified!" );

    TEST_FOR_EXCEPTION( distribution_rep.numParams() != 7,
			InvalidSpatialDistributionRepresentation,
			"Error: Three 1D distributions, the center "
			"coordinates and the axis must be specified for "
			"a spherical spatial distribution!" );
    
    valid_distribution = true;
  }

  TEST_FOR_EXCEPTION( !valid_distribution,
		      InvalidSpatialDistributionRepresentation,
		      "Error: The type of spatial distribution "
		      << distribution_rep << " could not be determined!" );
}

// Validate the axis name
void SpatialDistributionFactory::validateAxisName( 
						 const std::string& axis_name )
{
  TEST_FOR_EXCEPTION( axis_name.compare( "X" ) != 0 &&
		      axis_name.compare( "Y" ) != 0 &&
		      axis_name.compare( "Z" ) != 0,
		      InvalidSpatialDistributionRepresentation,
		      "Error: An invalid axis was specified (" 
		      << axis_name << ")!" );
}

// Convert the axis name to an Axis enum
Axis SpatialDistributionFactory::convertAxisNameToAxisEnum(
						 const std::string& axis_name )
{
  switch( axis_name.c_str()[0] )
  {
  case 'X':
    return X_AXIS;
  case 'Y':
    return Y_AXIS;
  case 'Z':
    return Z_AXIS;
  default:
    return UNDEFINED_AXIS;
  }
}

// Create a cartesian distribution
Teuchos::RCP<Utility::SpatialDistribution> 
SpatialDistributionFactory::createCartesianDistribution(
			       const Teuchos::ParameterList& distribution_rep )
{
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    distribution_rep.getEntryRCP( "X Distribution" );
  
  Teuchos::RCP<OneDDistribution> x_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  entry = distribution_rep.getEntryRCP( "Y Distribution" );
  
  Teuchos::RCP<OneDDistribution> y_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  entry = distribution_rep.getEntryRCP( "Z Distribution" );
  
  Teuchos::RCP<OneDDistribution> z_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  return Teuchos::RCP<SpatialDistribution>( 
			  new CartesianSpatialDistribution( x_distribution,
							    y_distribution,
							    z_distribution ) );
}

// Create a cylindrical distribution
Teuchos::RCP<Utility::SpatialDistribution> 
SpatialDistributionFactory::createCylindricalDistribution(
			       const Teuchos::ParameterList& distribution_rep )
{
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    distribution_rep.getEntryRCP( "R Distribution" );

  Teuchos::RCP<OneDDistribution> r_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  entry = distribution_rep.getEntryRCP( "Theta Distribution" );
  
  Teuchos::RCP<OneDDistribution> theta_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  entry = distribution_rep.getEntryRCP( "Axis Distribution" );
  
  Teuchos::RCP<OneDDistribution> axis_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  double center_x_position = 
    distribution_rep.get<double>( "Center X Position" );  
  
  double center_y_position = 
    distribution_rep.get<double>( "Center Y Position" );  
  
  double center_z_position = 
    distribution_rep.get<double>( "Center Z Position" );  
  
  std::string axis_name = 
    distribution_rep.get<std::string>( "Axis" );
  
  SpatialDistributionFactory::validateAxisName( axis_name );
  
  Axis axis = convertAxisNameToAxisEnum( axis_name );
  
  return Teuchos::RCP<SpatialDistribution>( 
			new CylindricalSpatialDistribution( r_distribution,
						            theta_distribution,
							    axis_distribution,
							    center_x_position,
							    center_y_position,
							    center_z_position,
							    axis ) );
}

// Create a spherical distribution
Teuchos::RCP<Utility::SpatialDistribution> 
SpatialDistributionFactory::createSphericalDistribution(
			       const Teuchos::ParameterList& distribution_rep )
{
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    distribution_rep.getEntryRCP( "R Distribution" );
  
  Teuchos::RCP<OneDDistribution> r_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  entry = distribution_rep.getEntryRCP( "Theta Distribution" );
  
  Teuchos::RCP<OneDDistribution> theta_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  entry = distribution_rep.getEntryRCP( "Mu Distribution" );
  
  Teuchos::RCP<OneDDistribution> mu_distribution = 
    OneDDistributionEntryConverterDB::convertEntry( entry );
  
  double center_x_position = 
    distribution_rep.get<double>( "Center X Position" );  
  
  double center_y_position = 
    distribution_rep.get<double>( "Center Y Position" );  
  
  double center_z_position = 
    distribution_rep.get<double>( "Center Z Position" );  
  
  std::string axis_name = 
    distribution_rep.get<std::string>( "Axis" );
  
  SpatialDistributionFactory::validateAxisName( axis_name );
  
  Axis axis = convertAxisNameToAxisEnum( axis_name );
  
  return Teuchos::RCP<SpatialDistribution>( 
			  new SphericalSpatialDistribution( r_distribution,
							    theta_distribution,
							    mu_distribution,
							    center_x_position,
							    center_y_position,
							    center_z_position,
							    axis ) );
}

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_SpatialDistributionFactory.cpp
//---------------------------------------------------------------------------//
