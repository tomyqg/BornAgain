// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorSphereLogNormalRadius.h
//! @brief     Defines and implements class FormFactorSphereLogNormalRadius.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHERELOGNORMALRADIUS_H_
#define FORMFACTORSPHERELOGNORMALRADIUS_H_
#include "MathFunctions.h"
#include "SafePointerVector.h"

#include "IFormFactor.h"
#include "FormFactorFullSphere.h"
#include <cassert>

class DistributionLogNormal;

//! @class FormFactorSphereLogNormalRadius
//! @ingroup formfactors
//! @brief The formfactor of sphere with log normal radius distribution.

class BA_CORE_API_ FormFactorSphereLogNormalRadius : public IFormFactorBorn
{
public:
    FormFactorSphereLogNormalRadius(double mean, double scale_param,
                                    size_t n_samples);
    virtual FormFactorSphereLogNormalRadius *clone() const;
    virtual ~FormFactorSphereLogNormalRadius();

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const;
    virtual bool isDistributedFormFactor() const { return true; }
    virtual void createDistributedFormFactors(
        std::vector<IFormFactor*>& form_factors,
        std::vector<double>& probabilities, size_t nbr_samples) const;

    virtual double getHeight() const;

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();
    void init_vectors();

private:
    double m_mean;
    double m_scale_param;
    size_t m_n_samples;

    DistributionLogNormal *mp_distribution;

    SafePointerVector<IFormFactorBorn> m_form_factors;
    std::vector<double> m_probabilities;
};

#endif /* FORMFACTORSPHERELOGNORMALRADIUS_H_ */


