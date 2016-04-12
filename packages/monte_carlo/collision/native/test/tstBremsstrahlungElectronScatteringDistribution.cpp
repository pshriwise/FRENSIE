//---------------------------------------------------------------------------//
//!
//! \file   tstBremsstrahlungElectronScatteringScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  Bremsstrahlung electron scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
  
// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectronScatteringDistribution>
  dipole_bremsstrahlung_distribution;

Teuchos::RCP<MonteCarlo::ElectronScatteringDistribution>
  tabular_bremsstrahlung_distribution;

Teuchos::RCP<MonteCarlo::ElectronScatteringDistribution>
  twobs_bremsstrahlung_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a simple 
 * (dipole distribution) photon is generated
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   DipoleBremsstrahlung )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 0.0009 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function 
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  dipole_bremsstrahlung_distribution->scatterElectron( electron,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.84838703016428E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed 2BS
 * photon is generated using the lower energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   2BS_bremsstrahlung )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[2] = 0.49; // Reject the angle
  fake_stream[3] = 0.5; // Sample a photon angle of 0.9118675275
  fake_stream[4] = 0.48; // Accept the angle

 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  twobs_bremsstrahlung_distribution->scatterElectron( electron,
                                                      bank,
                                                      shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.99834616322782E-01 , 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.612270260118, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed tabular
 * photon is generated using the lower energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   tabular_bremsstrahlung_lower_energy )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 0.0009 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 7.94968E-04 MeV and 1.18921E-02 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.0557151835328 from analytical function  

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  tabular_bremsstrahlung_distribution->scatterElectron( electron,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 8.84838703016428E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 1.51612969835718E-05 , 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.0592724905908 , 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed tabular 
 * photon is generated using the middle energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
		   tabular_bremsstrahlung_middle_energy )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 3.1622800E-01 MeV and 2.0 MeV distributions
  fake_stream[1] = 0.5; // Sample a photon angle of 9.912140279513E-03
 
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  tabular_bremsstrahlung_distribution->scatterElectron( electron,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.99834616322782E-01 , 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 1.65383677217787E-04, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 1.479601055066E-02, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );

}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
/* Check that an electron can be bremsstrahlung scattered and a detailed tabular 
 * photon is generated using the upper energy function
 */
TEUCHOS_UNIT_TEST( BremsstrahlungElectronScatteringDistribution,
                   tabular_bremsstrahlung_upper_energy )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::ElectronState electron( 1 );
  electron.setEnergy( 1E04 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  
  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.5; // Correlated sample the 1.22474E01 MeV and 1.0E5 MeV distributions
  fake_stream[1] = 0.5; // Sample angle 0.9999999986945 from analytical function  
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  tabular_bremsstrahlung_distribution->scatterElectron( electron,
                                                      bank,
                                                      shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( electron.getEnergy(), 9.9999922021191E+03, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getXDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getYDirection(), 0.0, 1e-12 );
  TEST_FLOATING_EQUALITY( electron.getZDirection(), 1.0, 1e-12 );

  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 7.79788089586180000E-03, 1e-12 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 0.9999999986945, 1e-12 );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  
  // Create the tabular angular distribution
  Teuchos::Array<double> energy_bins( 3 ); // (MeV)
  energy_bins[0] = 1e-6;
  energy_bins[1] = 1e-2;
  energy_bins[2] = 1e5;
  
  //! \todo Find real bremsstrahlung photon angular distribution
  Teuchos::Array<double> angular_distribution_values( 3 );
  angular_distribution_values[0] =  0.0;
  angular_distribution_values[1] =  0.9;
  angular_distribution_values[2] =  1.0;

  Teuchos::RCP<Utility::OneDDistribution> angular_distribution(
			    new Utility::TabularDistribution<Utility::LinLin>( 
						energy_bins,
						angular_distribution_values ) );

  // Extract the elastic scattering information data block (BREMI)
  Teuchos::ArrayView<const double> bremi_block(
				      xss_data_extractor->extractBREMIBlock() );

  // Extract the number of tabulated distributions
  int N = bremi_block.size()/3;

  // Extract the electron energy grid for bremsstrahlung energy distributions
  Teuchos::Array<double> energy_grid(bremi_block(0,N));

  // Extract the table lengths for bremsstrahlung energy distributions
  Teuchos::Array<double> table_length(bremi_block(N,N));

  // Extract the offsets for bremsstrahlung energy distributions
  Teuchos::Array<double> offset(bremi_block(2*N,N));

  // Extract the bremsstrahlung photon energy distributions block (BREME)
  Teuchos::ArrayView<const double> breme_block = 
    xss_data_extractor->extractBREMEBlock();

  // Create the bremsstrahlung scattering distributions
  MonteCarlo::BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
    scattering_distribution( N );
  
  for( unsigned n = 0; n < N; ++n )
  {
    scattering_distribution[n].first = energy_grid[n];

    scattering_distribution[n].second.reset( 
	  new Utility::HistogramDistribution(
		 breme_block( offset[n], table_length[n] ),
		 breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );

/*	  new Utility::TabularDistribution<Utility::LinLin>(
		 breme_block( offset[n], table_length[n] ),
		 breme_block( offset[n] + table_length[n], table_length[n] ),
         true ) );     */
  }

  // Create the scattering distributions
  dipole_bremsstrahlung_distribution.reset( 
		   new MonteCarlo::BremsstrahlungElectronScatteringDistribution( 
						       scattering_distribution ) );


  double upper_cutoff_energy = 1000;
  double lower_cutoff_energy = 0.001;

  tabular_bremsstrahlung_distribution.reset( 
		      new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
							scattering_distribution,
							angular_distribution,
                            lower_cutoff_energy, 
                            upper_cutoff_energy ) );

  twobs_bremsstrahlung_distribution.reset( 
		      new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
							scattering_distribution,
                            xss_data_extractor->extractAtomicNumber() ) );

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);  
}

//---------------------------------------------------------------------------//
// end tstIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
