// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/FormFactorCoherentPart.h
//! @brief     Defines class FormFactorCoherentPart.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCOHERENTPART_H
#define FORMFACTORCOHERENTPART_H

#include "Complex.h"
#include "EigenCore.h"
#include "WinDllMacros.h"
#include <memory>

class IFresnelMap;
class IFormFactor;
class SimulationElement;

//! Information about single particle form factor and specular info of the embedding layer.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorCoherentPart
{
public:
    FormFactorCoherentPart(IFormFactor* p_ff);
    FormFactorCoherentPart(const FormFactorCoherentPart& other);
    virtual ~FormFactorCoherentPart();

    complex_t evaluate(const SimulationElement& sim_element) const;
#ifndef SWIG
    Eigen::Matrix2cd evaluatePol(const SimulationElement& sim_element) const;
#endif

    void setSpecularInfo(const IFresnelMap* p_fresnel_map, size_t layer_index);
    double radialExtension() const;
private:
    std::unique_ptr<IFormFactor> mP_ff;
    const IFresnelMap* mp_fresnel_map;
    size_t m_layer_index;
};

#endif // FORMFACTORCOHERENTPART_H
