//---------------------------------------------------------------------------//
//!
//! \file   tstEquiprobableBinNeutronScatteringDistribution.cpp
//! \author Alex Bennett
//! \brief  Equiprobable bin neutron scattering distribution unit tests
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_UnitTestHarnessExtensions.hpp"
#include "Facemc_EquiprobableBinNeutronScatteringEnergyDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"


//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( EquiprobableBinNeutronScatteringEnergyDistribution, 
		   sampleEnergy_lower_bound )
{
   Facemc::EquiprobableBinNeutronScatteringEnergyDistribution::EnergyDistArray energy_grid;

   energy_grid.resize(2);

   energy_grid[0].first = 1.0;
   energy_grid[0].second.resize(5);
   energy_grid[0].second[0] = 1.0;
   energy_grid[0].second[1] = 2.0;
   energy_grid[0].second[2] = 3.0;
   energy_grid[0].second[3] = 4.0;
   energy_grid[0].second[4] = 5.0;

   energy_grid[1].first = 2.0;
   energy_grid[1].second.resize(5);
   energy_grid[1].second[0] = 2.0;
   energy_grid[1].second[1] = 3.0;
   energy_grid[1].second[2] = 4.0;
   energy_grid[1].second[3] = 5.0;
   energy_grid[1].second[4] = 6.0;

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   Facemc::EquiprobableBinNeutronScatteringEnergyDistribution distribution( energy_grid );

   TEST_COMPARE(distribution.sampleEnergy(0.5) ,==, 3)
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( EquiprobableBinNeutronScatteringEnergyDistribution, 
		   sampleEnergy_upper_bound )
{
   Facemc::EquiprobableBinNeutronScatteringEnergyDistribution::EnergyDistArray energy_grid;

   energy_grid.resize(2);

   energy_grid[0].first = 1.0;
   energy_grid[0].second.resize(5);
   energy_grid[0].second[0] = 1.0;
   energy_grid[0].second[1] = 2.0;
   energy_grid[0].second[2] = 3.0;
   energy_grid[0].second[3] = 4.0;
   energy_grid[0].second[4] = 5.0;

   energy_grid[1].first = 2.0;
   energy_grid[1].second.resize(5);
   energy_grid[1].second[0] = 2.0;
   energy_grid[1].second[1] = 3.0;
   energy_grid[1].second[2] = 4.0;
   energy_grid[1].second[3] = 5.0;
   energy_grid[1].second[4] = 6.0;

   // Create the fake stream
   std::vector<double> fake_stream( 1 );
   fake_stream[0] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   Facemc::EquiprobableBinNeutronScatteringEnergyDistribution distribution( energy_grid );

   TEST_COMPARE(distribution.sampleEnergy(3.0) ,==, 4)
}

//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( EquiprobableBinNeutronScatteringEnergyDistribution, 
		   sampleEnergy )
{
   Facemc::EquiprobableBinNeutronScatteringEnergyDistribution::EnergyDistArray energy_grid;

   energy_grid.resize(2);

   energy_grid[0].first = 1.0;
   energy_grid[0].second.resize(5);
   energy_grid[0].second[0] = 1.0;
   energy_grid[0].second[1] = 2.0;
   energy_grid[0].second[2] = 3.0;
   energy_grid[0].second[3] = 4.0;
   energy_grid[0].second[4] = 5.0;

   energy_grid[1].first = 2.0;
   energy_grid[1].second.resize(5);
   energy_grid[1].second[0] = 2.0;
   energy_grid[1].second[1] = 3.0;
   energy_grid[1].second[2] = 4.0;
   energy_grid[1].second[3] = 5.0;
   energy_grid[1].second[4] = 6.0;

   // Create the fake stream
   std::vector<double> fake_stream( 3 );
   fake_stream[0] = 0.5;
   fake_stream[1] = 0.75;
   fake_stream[2] = 0.5;

   Utility::RandomNumberGenerator::setFakeStream( fake_stream );

   Facemc::EquiprobableBinNeutronScatteringEnergyDistribution distribution( energy_grid );

   TEST_COMPARE(distribution.sampleEnergy(1.5) ,==, 4)
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  return Teuchos::UnitTestRepository::runUnitTestsFromMain( argc, argv );
}


//---------------------------------------------------------------------------//
// tstEquiprobableBinNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
