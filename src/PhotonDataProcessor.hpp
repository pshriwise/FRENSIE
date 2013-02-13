//---------------------------------------------------------------------------//
// \file PhotonDataProcessor.hpp
// \author Alex Robinson
// \brief Photon Data Processor declaration
//---------------------------------------------------------------------------//

#ifndef PHOTON_DATA_PROCESSOR_HPP
#define PHOTON_DATA_PROCESSOR_HPP

// FACEMC includes
#include "DataProcessorBase.hpp"
#include "DefaultParameterValues.hpp"

namespace FACEMC{

class PhotonDataProcessor : public DataProcessorBase
{

public:

  //! Constructor
  PhotonDataProcessor( const std::string epdl_file_name,
		       const std::string eadl_file_name,
		       const std::string compton_file_prefix,
		       const double energy_min = MIN_ENERGY_DEFAULT,
		       const double energy_max = MAX_ENERGY_DEFAULT );

  //! Destructor
  ~PhotonDataProcessor()
  { /* ... */ }

  //! Process Photon Data Files
  void processDataFiles();
  
private:
  
  // EPDL file name including absolute path to file
  const std::string d_epdl_file_name;

  // EADL file name including absolute path to file
  const std::string d_eadl_file_name;

  // Compton profile file name prefix including absolute path to files
  const std::string d_compton_file_prefix;

  // Minimum energy to read in from data tables
  const double d_energy_min;

  // Maximum energy to read in from data tables
  const double d_energy_max;

  //! Process EPDL file
  void processEPDLFile();

  //! Process EADL file
  void processEADLFile();

  //! Process Compton files
  void processComptonFiles();

  //! Create the Electron Shell Index Map
  /* \brief The Hartree-Fock Compton Profiles were compiled in the 1970s. The
   * shell filling that is done in the tables is out-of-date and not consistent
   * with the shell filling that is done in the 1997 EADL data file. To use the 
   * 1997 EADL data file with the Hartree-Fock Compton Profiles a map must be
   * made that relates the electron shell in the EADL data file to the correct
   * Hartree-Fock Compton Profile. Unfortunately, this will potentially be
   * different for every element.
   * \param atomic_number Atomic number of element the map will be made for
   * \param map[2] An empty 2D integer array where the index mapping will be
   * stored
   */
  void createElectronShellIndexMap( int atomic_number,
				    Teuchos::Array<int> map[2] );

};

} // end FACEMC namespace

#endif // end PHOTON_DATA_PROCESSOR_HPP

//---------------------------------------------------------------------------//
// end PhotonDataProcessor.hpp
//---------------------------------------------------------------------------//

  
