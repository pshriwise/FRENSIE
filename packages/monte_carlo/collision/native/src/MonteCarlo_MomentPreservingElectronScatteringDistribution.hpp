//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_MomentPreservingElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The moment preserving electron elastic scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MOMENT_PRESERVING_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_MOMENT_PRESERVING_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The moment preserving scattering distribution base class
class MomentPreservingElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                  public AdjointElectronScatteringDistribution
{

public:

  //! Typedef for the elastic discrete distribution
  typedef Teuchos::Array<Utility::Pair< double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElasticDistribution;

  //! Constructor
  MomentPreservingElectronScatteringDistribution(
                 const int atomic_number,
                 const double cutoff_angle_cosine,
                 const ElasticDistribution& discrete_scattering_distribution );

  //! Destructor
  virtual ~MomentPreservingElectronScatteringDistribution()
  { /* ... */ }

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
                        ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const;

  //! Randomly scatter the adjoint electron
  void scatterAdjointElectron( AdjointElectronState& adjoint_electron,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const;



protected:

   //! Sample an outgoing direction from the distribution
  void sampleAndRecordTrialsImpl( const double incoming_energy,
                                  double& scattering_angle_cosine,
                                  unsigned& trials ) const;

private:

  // elastic discrete scattering distribution
  ElasticDistribution d_discrete_scattering_distribution;

  // The cutoff angle cosine
  double d_cutoff_angle_cosine;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_MOMENT_PRESERVING_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
