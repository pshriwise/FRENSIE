//---------------------------------------------------------------------------//
// \file DataFileNames.hpp
// \author Alex Robinson
// \brief Names of the processed HDF5 data files
//---------------------------------------------------------------------------//

#ifndef DATA_FILE_NAMES_HPP
#define DATA_FILE_NAMES_HPP

//---------------------------------------------------------------------------//
// Photon data file
//---------------------------------------------------------------------------//

// Define the HDF5 photon data file name prefix
#define PHOTON_DATA_FILE_PREFIX "PhotonData-"

// Define the HDF5 photon data file coherent cross section location
#define COHERENT_CROSS_SECTION_LOC "/Basic_Data/Coherent_Cross_Section"

// Define the HDF5 photon data file incoherent cross section location
#define INCOHERENT_CROSS_SECTION_LOC "/Basic_Data/Incoherent_Cross_Section"

// Define the HDF5 photon data file total photoelectric cross section loc
#define PHOTOELECTRIC_CROSS_SECTION_LOC "/Basic_Data/Photoelectric_Cross_Section"

// Define the HDF5 photon data file subshell photoelectric cross section root
#define PHOTOELECTRIC_SUBSHELL_CROSS_SECTION_ROOT "/Fluorescence_Data/Photoelectric_Cross_Section/"

// Define the HDF5 photon data file pair production cross section location
#define PAIR_PRODUCTION_CROSS_SECTION_LOC "/Basic_Data/Pair_Production_Cross_Section"

// Define the HDF5 photon data file triplet production cross section location
#define TRIPLET_PRODUCTION_CROSS_SECTION_LOC "/Basic_Data/Triplet_Production_Cross_Section"

// Define the HDF5 photon data file atomic form factor location
#define ATOMIC_FORM_FACTOR_LOC "/Basic_Data/Atomic_Form_Factor"

// Define the HDF5 photon data file scattering function location
#define SCATTERING_FUNCTION_LOC "Basic_Data/Scattering_Function"

// Define the HDF5 photon data file electron shell cdf location
#define ELECTRON_SHELL_CDF_LOC "Doppler_Data/Electron_Shell_CDF"

// Define the HDF5 photon data file electron shell index map location
#define ELECTRON_SHELL_INDEX_MAP_LOC "Doppler_Data/Electron_Shell_Index_Map"

// Define the HDF5 photon data file electron shell binding energy location
#define ELECTRON_SHELL_BINDING_ENERGY_LOC "Doppler_Data/Electron_Shell_Binding_Energy"

// Define the HDF5 photon data file electron shell kinetic energy location
#define ELECTRON_SHELL_KINETIC_ENERGY_LOC "Doppler_Data/Electron_Shell_Kinetic_Energy"

// Define the HDF5 photon data file radiative transition probability root
#define RADIATIVE_TRANSITION_PROBABILITY_ROOT "Fluorescence_Data/Radiative_Transition_Probability/"

// Define the HDF5 photon data file nonradiative transition probability root
#define NONRADIATIVE_TRANSITION_PROBABILITY_ROOT "Fluorescence_Data/Nonradiative_Transition_Probability/"

//---------------------------------------------------------------------------//
// Adjoint Photon data file
//---------------------------------------------------------------------------//

// Define the HDF5 adjoint photon data file name prefix
#define ADJOINT_PHOTON_DATA_FILE_PREFIX "AdjointPhotonData-"

// Define the HDF5 electron data file name prefix
#define ELECTRON_DATA_FILE_PREFIX "ElectronData-"

// Define the HDF5 adjoint electron data file name prefix
#define ADJOINT_ELECTRON_DATA_FILE_PREFIX "AdjointElectronData-"

// Define the HDF5 file name suffix
#define DATA_FILE_SUFFIX ".h5"

#endif // end DATA_FILE_NAMES_HPP

//---------------------------------------------------------------------------//
// end DataFileNames.hpp
//---------------------------------------------------------------------------//
