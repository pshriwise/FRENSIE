//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedFullyTabularTwoDDistribution.hpp
//! \author Alex Robinson
//! \brief  The interpolated fully tabular two-dimensional dist. class decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP
#define UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_InterpolatedTabularTwoDDistributionImplBase.hpp"

namespace Utility{

namespace {

//! Helper class used to construct a cdf interpolation policy
template<typename YProcessingTag, typename XProcessingTag>
struct CDFInterpolationHelper
{ /* ... */ };

//! Helper class used to construct a LinLinLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLinLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LinIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLinLog CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLin cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LinIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLin CDFInterpPolicy;
};

//! Helper class used to construct a LinLogLog cdf interpolation policy
template<>
struct CDFInterpolationHelper<LogIndepVarProcessingTag,LogIndepVarProcessingTag>
{
  //! The cdf interpolation policy
  typedef LinLogLog CDFInterpPolicy;
};
  
} // end local namespace

/*! The unit-aware inteprolated fully tabular two-dimensional distribution
 * \ingroup two_d_distribution
 */
template<typename TwoDInterpPolicy,
         typename PrimaryIndependentUnit,
         typename SecondaryIndependentUnit,
         typename DependentUnit>
class UnitAwareInterpolatedFullyTabularTwoDDistribution : public UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> >
{

private:

  // The parent distribution type
  typedef UnitAwareInterpolatedTabularTwoDDistributionImplBase<TwoDInterpPolicy,UnitAwareFullyTabularTwoDDistribution<PrimaryIndependentUnit,SecondaryIndependentUnit,DependentUnit> > ParentType;

  // The base one-dimensional distribution type (UnitAwareTabularOneDDist)
  typedef typename ParentType::BaseOneDDistributionType BaseOneDDistributionType;

  // Typedef for QuantityTraits<double>
  typedef typename ParentType::QT QT;

  // Typedef for QuantityTraits<PrimaryIndepQuantity>
  typedef typename ParentType::PIQT PIQT;

  // Typddef for QuantityTraits<SecondaryIndepQuantity>
  typedef typename ParentType::SIQT SIQT;

  // Typedef for QuantityTriats<InverseSecondaryIndepQuantity>
  typedef typename ParentType::ISIQT ISIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef typename ParentType::DQT DQT;

  // The CDF interpolation policy
  typedef typename CDFInterpolationHelper<typename TwoDInterpPolicy::SecondIndepVarProcessingTag,typename TwoDInterpPolicy::FirstIndepVarProcessingTag>::CDFInterpPolicy CDFInterpPolicy;
  
public:
  
  //! The primary independent quantity type
  typedef typename ParentType::PrimaryIndepQuantity PrimaryIndepQuantity;

  //! The secondary independent quantity type
  typedef typename ParentType::SecondaryIndepQuantity SecondaryIndepQuantity;

  //! The inverse secondary independent quantity type
  typedef typename ParentType::InverseSecondaryIndepQuantity InverseSecondaryIndepQuantity;

  //! The dependent quantity type
  typedef typename ParentType::DepQuantity DepQuantity;

  //! The distribution type
  typedef typename ParentType::DistributionType DistributionType;

  //! Constructor
  UnitAwareInterpolatedFullyTabularTwoDDistribution(
                            const DistributionType& distribution,
                            const double fuzzy_boundary_tol = 1e-3,
                            const double evaluate_relative_error_tol = 1e-7,
                            const double evaluate_error_tol = 1e-16 )
    : ParentType( distribution, fuzzy_boundary_tol ),
      d_relative_error_tol( evaluate_relative_error_tol ),
      d_error_tol( evaluate_error_tol )
  { /* ... */ }

  //! Constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB>
  UnitAwareInterpolatedFullyTabularTwoDDistribution(
                   const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
                   const ArrayB<std::shared_ptr<const UnitAwareTabularOneDDistribution<SecondaryIndependentUnit,DependentUnit> > >& secondary_distributions,
                   const double fuzzy_boundary_tol = 1e-3,
                   const double evaluate_relative_error_tol = 1e-7,
                   const double evaluate_error_tol = 1e-16 )
    : ParentType( primary_indep_grid, secondary_distributions, fuzzy_boundary_tol ),
      d_relative_error_tol( evaluate_relative_error_tol ),
      d_error_tol( evaluate_error_tol )
  { /* ... */ }

  //! Raw constructor
  template<template<typename T, typename... Args> class ArrayA,
           template<typename T, typename... Args> class ArrayB,
           template<typename T, typename... Args> class SubarrayB,
           template<typename T, typename... Args> class ArrayC,
           template<typename T, typename... Args> class SubarrayC>
  UnitAwareInterpolatedFullyTabularTwoDDistribution(
        const ArrayA<PrimaryIndepQuantity>& primary_indep_grid,
        const ArrayB<SubarrayB<SecondaryIndepQuantity> >& secondary_indep_grids,
        const ArrayC<SubarrayC<DepQuantity> >& dependent_values,
        const double fuzzy_boundary_tol = 1e-3,
        const double evaluate_relative_error_tol = 1e-7,
        const double evaluate_error_tol = 1e-16 );

  //! Destructor
  ~UnitAwareInterpolatedFullyTabularTwoDDistribution()
  { /* ... */ }

  //! Correlated evaluate the distribution (unit based)
  DepQuantity correlatedEvaluate(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Correlated evaluate the distribution (unit based)
  DepQuantity correlatedEvaluate(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the distribution
  DepQuantity evaluateExact(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Correlated evaluate the secondary conditional PDF (unit based)
  InverseSecondaryIndepQuantity correlatedEvaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Correlated evaluate the secondary conditional PDF (unit based)
  InverseSecondaryIndepQuantity correlatedEvaluateSecondaryConditionalPDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional PDF
  InverseSecondaryIndepQuantity evaluateSecondaryConditionalPDFExact(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Correlated evaluate the secondary conditional CDF (unit based)
  double correlatedEvaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Correlated evaluate the secondary conditional CDF (unit based)
  double correlatedEvaluateSecondaryConditionalCDF(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Evaluate the secondary conditional CDF
  double evaluateSecondaryConditionalCDFExact(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF
  SecondaryIndepQuantity correlatedSampleSecondaryConditional(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var_value,
                const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF
  SecondaryIndepQuantity correlatedSampleSecondaryConditional(
                const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF
  SecondaryIndepQuantity sampleSecondaryConditionalExact(
                const PrimaryIndepQuantity primary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumber(
                const PrimaryIndepQuantity primary_indep_var_value,
                const double random_number ) const;

  //! Return a random correlated sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity correlatedSampleSecondaryConditionalWithRandomNumber(
                const PrimaryIndepQuantity primary_indep_var_value,
                const double random_number,
                const SecondaryIndepQuantity min_secondary_indep_var_value,
                const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity correlatedSampleSecondaryConditionalWithRandomNumber(
                const PrimaryIndepQuantity primary_indep_var_value,
                const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF at the CDF val
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumber(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const double random_number ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity correlatedSampleSecondaryConditionalInSubrange(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity min_secondary_indep_var_value,
                const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity correlatedSampleSecondaryConditionalInSubrange(
                const PrimaryIndepQuantity primary_indep_var_value,
                const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity correlatedSampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity min_secondary_indep_var_value,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random correlated sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity correlatedSampleSecondaryConditionalWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF in the subrange
  SecondaryIndepQuantity sampleSecondaryConditionalExactWithRandomNumberInSubrange(
            const PrimaryIndepQuantity primary_indep_var_value,
            const double random_number,
            const SecondaryIndepQuantity max_secondary_indep_var_value ) const;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const;

  //! Return a random sample from the secondary conditional PDF and the index
  SecondaryIndepQuantity sampleSecondaryConditionalAndRecordBinIndices(
                            const PrimaryIndepQuantity primary_indep_var_value,
                            SecondaryIndepQuantity& raw_sample,
                            unsigned& primary_bin_index,
                            unsigned& secondary_bin_index ) const;

private:

  //! Evaluate the distribution using the desired evaluation method
  template<typename LocalTwoDInterpPolicy,
           typename ReturnType,
           typename EvaluationMethod>
  ReturnType correlatedEvaluateImpl(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const SecondaryIndepQuantity secondary_indep_var_value,
                    const SecondaryIndepQuantity min_secondary_indep_var_value,
                    const SecondaryIndepQuantity max_secondary_indep_var_value,
                    EvaluationMethod evaluate,
                    const ReturnType below_lower_bound_return =
                    QuantityTraits<ReturnType>::zero(),
                    const ReturnType above_upper_bound_return =
                    QuantityTraits<ReturnType>::zero(),
                    unsigned max_number_of_iterations = 500 ) const;

  //! Evaluate the distribution using the desired evaluation method
  template<typename LocalTwoDInterpPolicy,
           typename ReturnType,
           typename EvaluationMethod>
  ReturnType evaluateExactImpl(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const SecondaryIndepQuantity secondary_indep_var_value,
                    EvaluationMethod evaluate,
                    const ReturnType below_lower_bound_return =
                    QuantityTraits<ReturnType>::zero(),
                    const ReturnType above_upper_bound_return =
                    QuantityTraits<ReturnType>::zero(),
                    unsigned max_number_of_iterations = 500 ) const;

  //! Correlated sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity correlatedSampleImpl(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    const SecondaryIndepQuantity min_secondary_indep_var_value,
                    const SecondaryIndepQuantity max_secondary_indep_var_value,
                    SampleFunctor sample_functor ) const;

  //! Sample from the distribution using the desired sampling functor
  template<typename SampleFunctor>
  SecondaryIndepQuantity sampleExactImpl(
                    const PrimaryIndepQuantity primary_indep_var_value,
                    SampleFunctor sample_functor ) const;

  // Return the correlated sampling functor for the desired bin boundary
  template<typename SampleFunctor>
  void getCorrelatedSampleInSubrangeFunctor(
                    typename DistributionType::const_iterator bin_boundary,
                    const SecondaryIndepQuantity max_secondary_indep_var_value,
                    const double random_number,
                    SampleFunctor& sample_functor,
                    SecondaryIndepQuantity& bin_boundary_max_value ) const;

  // The relative error tolerance for the evaluate impl schemes
  double d_relative_error_tol;

  // The error tolerance for the evaluate impl schemes
  double d_error_tol;
};

/*! \brief The interpolated fully tabular two-dimensional distribution 
 * (unit-agnostic)
 * \ingroup two_d_distributions
 */
template<typename TwoDInterpPolicy> using InterpolatedFullyTabularTwoDDistribution =
  UnitAwareInterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy,void,void,void>;
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_InterpolatedFullyTabularTwoDDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_INTERPOLATED_FULLY_TABULAR_TWO_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_InterpolatedFullyTabularTwoDDistribution.hpp
//---------------------------------------------------------------------------//