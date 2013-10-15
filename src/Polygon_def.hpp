//---------------------------------------------------------------------------//
//!
//! \file   Polygon_def.hpp
//! \author Alex Robinson
//! \brief  Polygon class declaration
//!
//---------------------------------------------------------------------------//

#ifndef POLYGON_DEF_HPP
#define POLYGON_DEF_HPP

// FACEMC Includes
#include "LinearAlgebraAlgorithms.hpp"
#include "VectorHelpers.hpp"

namespace FACEMC{

// Constructor
/*! \details The corners can be arranged in either clockwise or 
 * counterclockwise order. During the polygon construction, they will be
 * transformed to a counterclockwise ordering. This simplifies the creation
 * of complex polygons in R3.
 */ 
template<typename OrdinalType, typename ScalarType>
Polygon<OrdinalType,ScalarType>::Polygon( 
		const OrdinalType polygon_id,
		const std::list<Vector<ScalarType> > &ordered_polygon_corners )
  : PrintableObject( "ThreeSpacePolygon" ),
    ThreeSpaceObject( THREE_SPACE_POLYGON ),
    d_id( polygon_id ),
    d_corners( ordered_polygon_corners.size() ),
    d_min_coordinates(),
    d_max_coordinates(),
    d_area( ST::zero() ),
    d_centroid(),
    d_unit_normal(),
    d_rotation_matrix(),
    d_translation_vector()
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( d_corners.size() >= 4 );
  // Make sure that the polygon starts and ends with the same point
  testPrecondition( d_corners.front() == d_corners.back() );

  // Compute the unit normal to the plane of the polygon
  d_unit_normal = 
    Polygon<OrdinalType,ScalarType>::calculatePolygonPlaneUnitNormal( 
						     ordered_polygon_corners );
  
  // Find and set the minimum and maximum coordinates of the polygon
  Polygon<OrdinalType,ScalarType>::getExtremeCoordinates( 
						       ordered_polygon_corners,
						       d_min_coordinates,
						       d_max_coordinates );

  // Create and set the transformation matrix and vector
  Polygon<OrdinalType,ScalarType>::getTransformMatrixAndVector( 
					       d_unit_normal,
					       ordered_polygon_corners.front(),
					       d_rotation_matrix,
					       d_translation_vector );

  // Simplify the polygon by transforming the plane-of-polygon to xy-plane
  Polygon<OrdinalType,ScalarType>::transformPolygon( 
						   ordered_polygon_corners,
						   d_corners,
						   d_rotation_matrix,
						   d_translation_vector );

  // Compute and cache the polygon area
  d_area = Polygon<OrdinalType,ScalarType>::calculateArea( d_corners );
						  
  // Compute and cache the polygon centroid
  PointProjection transformed_centroid = 
    Polygon<OrdinalType,ScalarType>::calculateCentroid( d_corners,
							d_area );

  d_centroid = Polygon<OrdinalType,ScalarType>::applyReverseTransform(
							transformed_centroid,
							d_rotation_matrix,
							d_translation_vector );
}

// Return the polygon id
template<typename OrdinalType, typename ScalarType>
inline OrdinalType Polygon<OrdinalType,ScalarType>::getId() const
{
  return d_id;
}

// Return the area of the polygon
template<typename OrdinalType, typename ScalarType>
inline ScalarType Polygon<OrdinalType,ScalarType>::getArea() const
{
  return d_area;
}

// Return the minimum x-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType 
Polygon<OrdinalType,ScalarType>::getMinXCoordinate() const
{
  return d_min_coordinates[0];
}

// Return the maximum x-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType 
Polygon<OrdinalType,ScalarType>::getMaxXCoordinate() const
{
  return d_max_coordinates[0];
}

// Return the minimum y-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getMinYCoordinate() const
{
  return d_min_coordinates[1];
}

// Return the maximum y-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getMaxYCoordinate() const
{
  return d_max_coordinates[1];
}

// Return the minimum z-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getMinZCoordinate() const
{
  return d_min_coordinates[2];
}

// Return the maximum z-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getMaxZCoordinate() const
{
  return d_max_coordinates[2];
}

// Return the centroid x-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getCentroidXCoordinate() const
{
  return d_centroid[0];
}

// Return the centroid y-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getCentroidYCoordinate() const
{
  return d_centroid[1];
}

// Return the centroid z-coordinate
template<typename OrdinalType, typename ScalarType>
inline ScalarType
Polygon<OrdinalType,ScalarType>::getCentroidZCoordinate() const
{
  return d_centroid[2];
}

// Return the polygon centroid
template<typename OrdinalType, typename ScalarType>
Vector<ScalarType>
Polygon<OrdinalType,ScalarType>::getCentroid() const
{
  return d_centroid;
}

// Return the unit normal to the plane of the polygon
template<typename OrdinalType, typename ScalarType>
Vector<ScalarType> 
Polygon<OrdinalType,ScalarType>::getPolygonPlaneUnitNormal() const
{
  return d_unit_normal;
}

// Print method that defines the behavior of the std::stream << operator
template<typename OrdinalType, typename ScalarType>
void Polygon<OrdinalType,ScalarType>::print( std::ostream &os ) const
{
  os << "Id: " << d_id << std::endl;
  os << "Area: " << d_area << std::endl;
  os << "Centroid: {" << d_centroid[0] << "," << d_centroid[1] << ","
     << d_centroid[2] << "}" << std::endl;
  os << "Unit Normal: {" << d_unit_normal[0] << "," << d_unit_normal[1] << ","
     << d_unit_normal[2] << "}" << std::endl;
  os << "Ordered Corners: ";
  
  typename std::list<PointProjection>::const_iterator corner, end_corner;
  corner = d_corners.begin();
  end_corner = d_corners.end();

  while( corner != end_corner )
  {
    Vector<ScalarType> original_point = 
      Polygon<OrdinalType,ScalarType>::applyReverseTransform( 
							*corner,
							d_rotation_matrix,
							d_translation_vector );
    os << "{" << original_point[0] << ","
       << original_point[1] << ","
       << original_point[2] << "} ";
      
    ++corner;
  }

  os << std::endl;
}

// Compute the unit normal to the plane of the polygon
template<typename OrdinalType, typename ScalarType>
Vector<ScalarType>
Polygon<OrdinalType,ScalarType>::calculatePolygonPlaneUnitNormal(
			const std::list<Vector<ScalarType> > &polygon_corners )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( polygon_corners.size() >= 4 );
  
  typename std::list<Vector<ScalarType> >::const_iterator first_point, 
    second_point, third_point;
  
  first_point = polygon_corners.begin();
  
  second_point = first_point;
  ++second_point;
    
  third_point = second_point;
  ++third_point;

  // The orientation of these vector assures that the transformed polygon
  // will have a left-handed orientation on the xy-plane (needed for pos. area)
  Vector<ScalarType> polygon_vector_1((*second_point)[0] - (*third_point)[0],
				      (*second_point)[1] - (*third_point)[1],
				      (*second_point)[2] - (*third_point)[2] );

  Vector<ScalarType> polygon_vector_2((*second_point)[0] - (*first_point)[0],
				      (*second_point)[1] - (*first_point)[1],
				      (*second_point)[2] - (*first_point)[2] );

  Vector<ScalarType> polygon_plane_normal =
    LinearAlgebra::computeCrossProduct( polygon_vector_1, polygon_vector_2 );
  polygon_plane_normal.normalize();
  

  return polygon_plane_normal;
}

// Find and the maximum and minimum coordinates of the polygon
template<typename OrdinalType, typename ScalarType>
void Polygon<OrdinalType,ScalarType>::getExtremeCoordinates(
			 const std::list<Vector<ScalarType> > &polygon_corners,
			 Vector<ScalarType> &min_coordinates,
			 Vector<ScalarType> &max_coordinates )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( polygon_corners.size() >= 4 );

  // Initialize the min coordinates
  min_coordinates[0] = ST::rmax();
  min_coordinates[1] = ST::rmax();
  min_coordinates[2] = ST::rmax();

  // Initialize the max coordinates
  max_coordinates[0] = -ST::rmax();
  max_coordinates[1] = -ST::rmax();
  max_coordinates[2] = -ST::rmax();

  typename std::list<Vector<ScalarType> >::const_iterator corner, end_corner;
  corner = polygon_corners.begin();
  end_corner = polygon_corners.end();

  while( corner != end_corner )
  {
    if( (*corner)[0] < min_coordinates[0] )
      min_coordinates[0] = (*corner)[0];
    
    if( (*corner)[0] > max_coordinates[0] )
      max_coordinates[0] = (*corner)[0];
    
    if( (*corner)[1] < min_coordinates[1] )
      min_coordinates[1] = (*corner)[1];

    if( (*corner)[1] > max_coordinates[1] )
      max_coordinates[1] = (*corner)[1];
    
    if( (*corner)[2] < min_coordinates[2] )
      min_coordinates[2] = (*corner)[2];

    if( (*corner)[2] > max_coordinates[2] )
      max_coordinates[2] = (*corner)[2];

    ++corner;
  }
}

// Create and set the transformation matrix and vector
template<typename OrdinalType, typename ScalarType>
void Polygon<OrdinalType,ScalarType>::getTransformMatrixAndVector( 
			   const Vector<ScalarType> &polygon_plane_unit_normal,
			   const Vector<ScalarType> &polygon_corner,
			   Matrix<ScalarType> &rotation_matrix,
			   Vector<ScalarType> &translation_vector )
{
  // Make sure the unit normal is valid
  testPrecondition( ST::magnitude( polygon_plane_unit_normal.normTwo() - 
				   ST::one() ) < ST::prec() );

  // Create the rotation matrix
  rotation_matrix = createRotationMatrixFromUnitVectors( 
					     polygon_plane_unit_normal,
					     createZAxisVector<ScalarType>() );

  // Determine the rotated polygon plane constant
  Vector<ScalarType> rotation_matrix_row_3( rotation_matrix( 2, 0 ), 
					    rotation_matrix( 2, 1 ),
					    rotation_matrix( 2, 2 ) );
  
  ScalarType rotated_plane_constant = 
    rotation_matrix_row_3.dot( polygon_corner );

  // The translation will only need to occur in the z-direction
  ScalarType delta_z = -rotated_plane_constant;

  // Create the translation vector
  translation_vector = createVector<ScalarType>( 0.0, 0.0, delta_z );
}

// Simplify the polygon by transforming plane-of-polygon to x-y plane
template<typename OrdinalType, typename ScalarType>
void Polygon<OrdinalType,ScalarType>::transformPolygon(
		      const std::list<Vector<ScalarType> > &polygon_corners,
		      std::list<PointProjection> &transformed_polygon_corners,
		      const Matrix<ScalarType> &rotation_matrix,
		      const Vector<ScalarType> &translation_vector )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( polygon_corners.size() >= 4 );
  testPrecondition( polygon_corners.size() == 
		    transformed_polygon_corners.size() );

  typename std::list<Vector<ScalarType> >::const_iterator corner, end_corner;
  corner = polygon_corners.begin();
  end_corner = polygon_corners.end();

  typename std::list<PointProjection>::iterator transformed_corner = 
    transformed_polygon_corners.begin();

  while( corner != end_corner )
  {
    *transformed_corner = Polygon<OrdinalType,ScalarType>::applyTransform(
							  *corner,
							  rotation_matrix,
							  translation_vector );
    ++corner;
    ++transformed_corner;
  }
}

// Apply transform to a point on the polygon
template<typename OrdinalType, typename ScalarType>
typename Polygon<OrdinalType,ScalarType>::PointProjection
Polygon<OrdinalType,ScalarType>::applyTransform( 
				 const Vector<ScalarType> &point_on_polygon,
				 const Matrix<ScalarType> &rotation_matrix,
				 const Vector<ScalarType> &translation_vector )
{
  // Make sure that the rotation matrix is valid (3x3 and orthonormal)
  testPrecondition( rotation_matrix.isOrthonormal() );

  // Apply the transformation (x' = R*x + x_0)
  Vector<ScalarType> transformed_point( point_on_polygon );
  transformed_point *= rotation_matrix;
  transformed_point += translation_vector;

  // Make sure that the transform was successful
  testPostcondition( ST::magnitude( transformed_point[2] ) < ST::prec() );

  // Return the point
  PointProjection new_point( transformed_point[0], transformed_point[1] );
  return new_point;
}

// Apply reverse transform to a point on the polygon
template<typename OrdinalType, typename ScalarType>
Vector<ScalarType>
Polygon<OrdinalType,ScalarType>::applyReverseTransform( 
				 const PointProjection &xy_plane_point,
				 const Matrix<ScalarType> &rotation_matrix,
				 const Vector<ScalarType> &translation_vector )
{
  // Make sure that the rotation matrix is valid (3x3 and orthonormal)
  testPrecondition( rotation_matrix.isOrthonormal() );

  // Convert the point to a vector (x' - x_0)
  Vector<ScalarType> point( xy_plane_point.first - translation_vector[0],
			    xy_plane_point.second - translation_vector[1],
			    -translation_vector[2] );

  // Apply the reverse transformation ( x = R^T*(x' - x_0) )
  Vector<ScalarType> transformed_point;
  transformed_point.multiply( 1.0,
			      rotation_matrix,
			      true,
			      point,
			      0.0 );  

  return transformed_point;
}

// Compute the area of a simplified polygon
template<typename OrdinalType,typename ScalarType>
ScalarType Polygon<OrdinalType,ScalarType>::calculateArea(
			 const std::list<PointProjection> &simplified_polygon )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( simplified_polygon.size() >= 4 );

  typename std::list<PointProjection>::const_iterator first_corner, 
    second_corner, end_corner;
  
  first_corner = simplified_polygon.begin();
  
  second_corner = first_corner;
  ++second_corner;
  
  end_corner = simplified_polygon.end();

  ScalarType area = ST::zero();

  // A = 0.5 * Sum_{i=0}^{n-1}(x_i + x_{i+1})*(y_{i+1} - y_i)
  while( second_corner != end_corner )
  {
    area += (first_corner->first*second_corner->second - 
	     second_corner->first*first_corner->second);

    ++first_corner;
    ++second_corner;
  }

  area /= 2;

  // Make sure that the calculate area is physical
  testPostcondition( area > ST::zero() );
  testPostcondition( !ST::isnaninf( area ) );

  return area;
}

// Calculate the polygon centroid
template<typename OrdinalType,typename ScalarType>
typename Polygon<OrdinalType,ScalarType>::PointProjection
Polygon<OrdinalType,ScalarType>::calculateCentroid( 
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( simplified_polygon.size() >= 4 );

  PointProjection centroid;

  centroid.first = 
    Polygon<OrdinalType,ScalarType>::calculateCentroidXCoordinate( 
							    simplified_polygon,
							    polygon_area );

  centroid.second = 
    Polygon<OrdinalType,ScalarType>::calculateCentroidYCoordinate( 
							    simplified_polygon,
							    polygon_area );
  return centroid;
}

// Compute the x-coordinate of a simplified polygon centroid
template<typename OrdinalType,typename ScalarType>
ScalarType Polygon<OrdinalType,ScalarType>::calculateCentroidXCoordinate(
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( simplified_polygon.size() >= 4 );

  typename std::list<PointProjection>::const_iterator first_corner, 
    second_corner, end_corner;
  
  first_corner = simplified_polygon.begin();
  
  second_corner = first_corner;
  ++second_corner;
  
  end_corner = simplified_polygon.end();

  ScalarType centroid_x_coord = ST::zero();

  // x_c = (6*Area)^{-1} * Sum_{i=0}^{n-1}(x_{i+1}^2 + x_{i+1}*x_i + x_i^2)*
  //                                      (y_{i+1} - y_i)
  while( second_corner != end_corner )
  {
    centroid_x_coord += (first_corner->first + second_corner->first)*
      (first_corner->first*second_corner->second - 
       second_corner->first*first_corner->second);

    ++first_corner;
    ++second_corner;
  }

  centroid_x_coord /= 6*polygon_area;

  // Make sure that the calculated coordinate is physical
  testPostcondition( !ST::isnaninf( centroid_x_coord ) );
  
  return centroid_x_coord;
}

// Compute the y-coordinate of a simplified polygon centroid
template<typename OrdinalType,typename ScalarType>
ScalarType Polygon<OrdinalType,ScalarType>::calculateCentroidYCoordinate(
			  const std::list<PointProjection> &simplified_polygon,
			  const ScalarType polygon_area )
{
  // The polygon must have at least 4 corners (3 + copy of first point)
  testPrecondition( simplified_polygon.size() >= 4 );

  typename std::list<PointProjection>::const_iterator first_corner, 
    second_corner, end_corner;
  
  first_corner = simplified_polygon.begin();
  
  second_corner = first_corner;
  ++second_corner;
  
  end_corner = simplified_polygon.end();

  ScalarType centroid_y_coord = ST::zero();

  while( second_corner != end_corner )
  {
    centroid_y_coord += (first_corner->second + second_corner->second)*
      (first_corner->first*second_corner->second - 
       second_corner->first*first_corner->second);

    ++first_corner;
    ++second_corner;
  }

  centroid_y_coord /= 6*polygon_area;

  // Make sure that the calculate coordinate is physical
  testPostcondition( !ST::isnaninf( centroid_y_coord ) );

  return centroid_y_coord;
}

} // end FACEMC namespace

#endif // end POLYGON_DEF_HPP

//---------------------------------------------------------------------------//
// end Polygon_def.hpp
//---------------------------------------------------------------------------//

