// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactorSphereUniformRadius.h
//! @brief     Defines class .
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHEREUNIFORMRADIUS_H_
#define FORMFACTORSPHEREUNIFORMRADIUS_H_

#include "MathFunctions.h"

#include "IFormFactor.h"
#include "FormFactorFullSphere.h"
#include <cassert>

//! Integrated full sphere form factor over a uniform distribution of radii
class BA_CORE_API_ FormFactorSphereUniformRadius : public IFormFactorBorn
{
public:
    FormFactorSphereUniformRadius(double mean, double full_width);
    virtual FormFactorSphereUniformRadius *clone() const;
    virtual ~FormFactorSphereUniformRadius();

    virtual void accept(ISampleVisitor *visitor) const { visitor->visit(this); }

    virtual int getNumberOfStochasticParameters() const;
    virtual bool isDistributedFormFactor() const { return true; }
    virtual void createDistributedFormFactors(
        std::vector<IFormFactor*>& form_factors,
        std::vector<double>& probabilities, size_t nbr_samples) const;

    virtual double getHeight() const { return 2.0*m_mean; }

    virtual complex_t evaluate_for_q(const cvector_t& q) const;

protected:
    virtual void init_parameters();

private:
    bool checkParameters() const;
    double m_mean; //!< This is the mean radius
    double m_full_width; //!< This is the full width of the radius distribution
};

#endif /* FORMFACTORSPHEREUNIFORMRADIUS_H_ */