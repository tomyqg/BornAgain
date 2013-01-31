#ifndef FITSUITE_H
#define FITSUITE_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FitSuite.h
//! @brief  Definition of FitSuite class
//! @author Scientific Computing Group at FRM II
//! @date   05.10.2012

#include "IObserver.h"
#include "FitSuiteStrategies.h"
#include "FitSuiteObjects.h"
#include "FitSuiteParameters.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"
#include "FitSuiteFunctions.h"
#include <string>

class Experiment;
class ParameterPool;


//- -------------------------------------------------------------------
//! @class FitSuite
//! @brief Main class to perform fitting
//- -------------------------------------------------------------------
class FitSuite : public IObservable
{
public:
    FitSuite();
    virtual ~FitSuite();

    //! clear all and prepare for the next fit
    void clear();

    //! add pair of (experiment, real data) for consecutive simulation
    void addExperimentAndRealData(const Experiment &experiment, const OutputData<double > &real_data, const IChiSquaredModule &chi2_module=ChiSquaredModule());

    //! add fit parameter
    void addFitParameter(const std::string &name, double value, double step, const AttLimits &attlim=AttLimits::limitless(), double error=0.0);

    //! add fit strategy
    void addFitStrategy(IFitSuiteStrategy *strategy);

    //! set minimizer
    void setMinimizer(IMinimizer *minimizer) { delete m_minimizer;  m_minimizer = minimizer; }
    //! get minimizer
    IMinimizer *getMinimizer() { return m_minimizer; }

    //! link fitting parameters to parameters defined in experiments
    virtual void link_fit_parameters();

    //! run fitting which may consist of several minimization rounds
    virtual void runFit();

    //! run single minimization round
    virtual void minimize();

    //! return reference to the kit with data
    FitSuiteObjects *getFitObjects() { return &m_fit_objects; }

    //! return reference to fit parameters
    FitSuiteParameters *getFitParameters() { return &m_fit_parameters; }

    //! if the last iteration is done (used by observers to print summary)
    bool isLastIteration() const { return m_is_last_iteration; }

    //! get current number of minimization function calls
    size_t getNCalls() const;

    //! get the number of current strategy
    size_t getNStrategy() const { return m_fit_strategies.getNStrategy(); }

    //! print results of the screen
    void printResults() const;

private:
    //! disabled copy constructor and assignment operator
    FitSuite &operator=(const FitSuite &);
    FitSuite(const FitSuite &);

    //! check if all prerequisites to run fit fit are filled
    bool check_prerequisites() const;

    FitSuiteObjects m_fit_objects; //! kit which contains sets of <experiment,real_data,chi_module> to fit
    FitSuiteParameters m_fit_parameters; //! collection of fit parameters
    FitSuiteStrategies m_fit_strategies; //! collection of strategies which are executed before every minimization round
    IMinimizer  *m_minimizer; //! minimization engine
    FitSuiteChiSquaredFunction m_function_chi2;
    FitSuiteGradientFunction m_function_gradient;

    bool m_is_last_iteration; //! set to true after last iteration complete
};

#endif // FITSUITE_H