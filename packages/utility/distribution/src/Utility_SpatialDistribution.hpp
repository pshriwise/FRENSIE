//---------------------------------------------------------------------------//
//!
//! \file   Utility_SpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Spatial distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_SPATIAL_DISTRIBUTION_HPP
#define UTILITY_SPATIAL_DISTRIBUTION_HPP

namespace Utility{

//! Spatial distribution base class
class SpatialDistribution
{

public:

  //! Constructor
  SpatialDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~SpatialDistribution()
  { /* ... */ }

  //! Evaluate the spatial distribution
  virtual double evaluate( const double cartesian_point[3] ) const = 0;

  //! Evaluate the spatial distribution PDF
  virtual double evaluatePDF( const double cartesian_point[3] ) const = 0;

  //! Return a random (cartesian) sample from the distribution (x, y, z)
  virtual void sample( double sampled_point[3] ) const = 0;

  //! Check if the distribution is uniform
  virtual bool isUniform() const = 0;
};

} // end Utility namespace

#endif // end UTILITY_SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utiliy_SpatialDistribution.hpp
//---------------------------------------------------------------------------//
