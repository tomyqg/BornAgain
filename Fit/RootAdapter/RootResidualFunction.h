// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/RootAdapter/RootResidualFunction.h
//! @brief     Declares class RootResidualFunction.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ROOTRESIDUALFUNCTION_H
#define ROOTRESIDUALFUNCTION_H

#include "KernelTypes.h"

#ifdef _WIN32
#include "Math/FitMethodFunction.h"
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include "Math/FitMethodFunction.h"
#pragma GCC diagnostic pop
#endif

//! Minimizer function with access to single data element residuals,
//! required by Fumili2 and GSLMultiMin minimizers.

class RootResidualFunction : public ROOT::Math::FitMethodFunction
{
public:
    typedef ROOT::Math::BasicFitMethodFunction<ROOT::Math::IMultiGenFunction>::Type_t Type_t;

    //! Constructs RootResidualFunction
    //! @param fun_gradient: user function to call
    //! @param npars: number of fit parameters
    //! @param ndatasize: number of residual elements in dataset
    RootResidualFunction(gradient_function_t fun_gradient, size_t npars, size_t ndatasize);

    Type_t Type() const override;

    ROOT::Math::IMultiGenFunction* Clone() const override;

    //! Evaluation of single data element residual. Will be called by ROOT minimizer.
    double DataElement(const double* pars, unsigned int index,
                       double* gradients = 0) const override;

private:
    //! evaluation of chi2
    double DoEval(const double* pars) const override;

    size_t m_npars;
    size_t m_datasize;
    gradient_function_t m_fun_gradient; //!< User function to get residual and gradients.
};

#endif //  ROOTRESIDUALFUNCTION_H
