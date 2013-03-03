//---------------------------------------------------------------------------//
// \file EPDL97DataProcessor.cpp
// \author Alex Robinson
// \brief EPDL97 data processor base class non-template member function 
// definitions
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>
#include <limits>
#include <fstream>
#include <iostream>

// FACEMC Includes
#include "EPDL97DataProcessor.hpp"
#include "ElectronShells.hpp"
#include "FACEMC_Assertion.hpp"
#include "Tuple.hpp"

namespace FACEMC{

//! Read the first table header
void EPDL97DataProcessor::readFirstTableHeader( std::ifstream& datafile,
						unsigned int &atomic_number,
						unsigned int &outgoing_particle_designator,
						double &atomic_weight,
						unsigned int &interpolation_flag )
{
  // The datafile must be valid
  testPrecondition( datafile );
  
  // Variables for reading in EPDL data file header 1
  //  the variable names are consistent with the names in the EPDL docs,
  //  the variables are one char longer than needed to account for the '\0' char
  char zaid[7];
  char space[2];
  char Yi[3];
  char Yo[3];
  char Al[10];
  char Ar[3];
  char date[7];
  char iflag[2];
  char extra[40];

  datafile.get( zaid, 7 );
  datafile.get( space, 2 );
  datafile.get( Yi, 3 );
  datafile.get( space, 2 );
  datafile.get( Yo, 3 );
  datafile.get( space, 2 );
  datafile.get( Al, 10 );
  datafile.get( Ar, 3 );
  datafile.get( space, 2 );
  datafile.get( date, 7 );
  datafile.get( iflag, 2 );
  datafile.getline( extra, 40 );

  atomic_number = atoi(zaid)/1000;
  outgoing_particle_designator = atoi(Yo);
  atomic_weight = extractValue<double>( Al, Ar );
  interpolation_flag = atoi(iflag);

  // The data file must still be valid (or the eof bit is set)
  testPostcondition( (datafile || datafile.eof()) );
}

//! Read the second table header
void EPDL97DataProcessor::readSecondTableHeader( std::ifstream& datafile, 
						 unsigned int &reaction_type,
						 unsigned int &electron_shell )
{
  // The datafile must be valid
  testPrecondition( datafile );
  
  // Variables for reading in the EPDL data file header 2
  //  the variable names are consistent with the names in the EPDL docs,
  //  the variables are one char longer than needed to account for the '\0' char
  char C [3];
  char I [4];
  char S [4];
  char garbage [14];
  char X1l [10];
  char X1r [3];
  char extra [38];

  datafile.get( C, 3 );
  datafile.get( I, 4 );
  datafile.get( S, 4 );
  datafile.get( garbage, 14 );
  datafile.get( X1l, 10 );
  datafile.get( X1r, 3 );
  datafile.getline( extra, 38 );
  
  reaction_type = atoi(C)*1000 + atoi(I);
  electron_shell = extractValue<unsigned int>( X1l, X1r ); 

  // The data file must still be valid
  testPostcondition( datafile );
}

//! Skip two column table in EPDL file
void EPDL97DataProcessor::skipTwoColumnTable( std::ifstream &datafile )
{
  // The datafile must be valid
  testPrecondition( datafile );
  
  char line[23];
  char test[] = "                      ";
  char end_of_table[50];

  do
  {
    datafile.get( line, 23 );
    datafile.ignore();
  }
  while( strcmp( line, test ) != 0 );
    

  // Read rest of end of table line
  datafile.getline( end_of_table, 50 );

  // The data file must still be valid
  testPostcondition( datafile );
}

//! Skip three column table in EPDL file
void EPDL97DataProcessor::skipThreeColumnTable( std::ifstream &datafile )
{
  // The datafile must be valid
  testPrecondition( datafile.is_open() );
  
  char line[34];
  char test[] = "                                 ";
  char end_of_table[40];
  
  do
  {
    datafile.get( line, 34 );
    datafile.ignore();
  }
  while( strcmp( line, test ) != 0 );
    
  // Read rest of end of table line
  datafile.getline( end_of_table, 40 );
}

//! Read three column table in EPDL file
void EPDL97DataProcessor::readThreeColumnTable( std::ifstream &datafile,
						Teuchos::Array<Trip<unsigned int,double,double> > &data )
{
  // The datafile must be valid
  testPrecondition( datafile );
  
  char data1_l [10];
  char data1_r [3];
  char data2_l [10];
  char data2_r [3];
  char data3_l [10];
  char data3_r [3];
  char end_of_table [40];
  char test []=  "         ";

  // Make sure that the data array is empty
  data.clear();

  // Data point from table
  Trip<unsigned int,double,double> data_point;

  // Read the table one line at a time
  do
  {
    datafile.get( data1_l, 10 );
    datafile.get( data1_r, 3 );
    datafile.get( data2_l, 10 );
    datafile.get( data2_r, 3 );
    datafile.get( data3_l, 10 );
    datafile.get( data3_r, 3 );
    datafile.ignore();
    
    if( strcmp( data1_l, test ) != 0 )
    {
      data_point.first = extractValue<unsigned int>( data1_l, data1_r );
      data_point.second = extractValue<double>( data2_l, data2_r );
      data_point.third = extractValue<double>( data3_l, data3_r );
      
      data.push_back( data_point );
    }
  }
  while( strcmp( data1_l, test ) != 0 );

  // Read rest of end of table line
  datafile.getline( end_of_table, 40 );

  // The data file must still be valid
  testPostcondition( datafile );
}

//! Skip four column table in EPDL file
void EPDL97DataProcessor::skipFourColumnTable( std::ifstream &datafile )
{
  // The datafile must be valid
  testPrecondition( datafile );
  
  char line[45];
  char test[] = "                                            ";
  char end_of_table[28];
  
  do
  {
    datafile.get( line, 45 );
    datafile.ignore();
  }
  while( strcmp( line, test ) != 0 );
    
  // Read rest of end of table line
  datafile.getline( end_of_table, 28 );

  // The data file must still be valid
  testPostcondition( datafile );
}

//! Read four column table in EPDL file
void EPDL97DataProcessor::readFourColumnTable( std::ifstream &datafile,
					       Teuchos::Array<Quad<unsigned int,unsigned int,double,double> > &data )
{
  // The datafile must be valid
  testPrecondition( datafile );
  
  char data1_l [10];
  char data1_r [3];
  char data2_l [10];
  char data2_r [3];
  char data3_l [10];
  char data3_r [3];
  char data4_l [10];
  char data4_r [3];
  char end_of_table [28];
  char test []=  "         ";

  // Make sure that the data array is empty
  data.clear();

  // Data point from table
  Quad<unsigned int,unsigned int,double,double> data_point;

  // Read the table one line at a time
  do
  {
    datafile.get( data1_l, 10 );
    datafile.get( data1_r, 3 );
    datafile.get( data2_l, 10 );
    datafile.get( data2_r, 3 );
    datafile.get( data3_l, 10 );
    datafile.get( data3_r, 3 );
    datafile.get( data4_l, 10 );
    datafile.get( data4_r, 3 );
    datafile.ignore();
    
    if( strcmp( data1_l, test ) != 0 )
    {
      data_point.first = extractValue<unsigned int>( data1_l, data1_r );
      data_point.second = extractValue<unsigned int>( data2_l, data2_r );
      data_point.third = extractValue<double>( data3_l, data3_r );
      data_point.fourth = extractValue<double>( data4_l, data4_r );

      data.push_back( data_point );
    }
  }
  while( strcmp( data1_l, test ) != 0 );

  // Read rest of end of table line
  datafile.getline( end_of_table, 28 );

  // The data file must still be valid
  testPostcondition( datafile );
}

//! Convert an unsigned int to an electron shell string
std::string EPDL97DataProcessor::uintToShellStr( unsigned int shell )
{
  std::stringstream shell_str;
  shell_str << shell;
  return shell_str.str();
}  

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end EPDL97DataProcessor.cpp
//---------------------------------------------------------------------------//


