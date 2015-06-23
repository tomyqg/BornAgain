// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/inc/ParticleInfo.h
//! @brief     Defines class ParticleInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEINFO_H
#define PARTICLEINFO_H

#include "ICompositeSample.h"
#include "IParticle.h"

#include <boost/scoped_ptr.hpp>

//! @class ParticleInfo
//! @ingroup samples
//! @brief Holds additional information about particle.
//!
//! Used in ParticleLayout

class BA_CORE_API_ ParticleInfo : public ICompositeSample
{
public:
    ParticleInfo(const IParticle &p_particle, double abundance = 1.0);

    virtual ~ParticleInfo()
    {
    }

    virtual ParticleInfo *clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleInfo *cloneInvertB() const;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor *visitor) const
    {
        visitor->visit(this);
    }

    //! Returns particle.
    const IParticle *getParticle() const
    {
        return mP_particle.get();
    }

    //! Returns particle position, including depth.
    kvector_t getPosition() const
    {
        return mP_particle->getPosition();
    }

    //! Sets particle position, including depth.
    void setPosition(kvector_t position);

    //! Returns abundance.
    double getAbundance() const
    {
        return m_abundance;
    }

    //! Sets abundance.
    void setAbundance(double abundance)
    {
        m_abundance = abundance;
    }

    //! Sets the ambient material
    void setAmbientMaterial(const IMaterial &material)
    {
        mP_particle->setAmbientMaterial(material);
    }

    //! Applies transformation to wrapped particle by composing it with the existing one
    void applyRotation(const IRotation &rotation);

    //! Applies extra translation to wrapped particle by adding it to the current one
    void applyTranslation(kvector_t displacement);

protected:
    virtual void init_parameters();

    virtual void print(std::ostream &ostr) const;

    boost::scoped_ptr<IParticle> mP_particle;
    double m_abundance;
};

#endif /* PARTICLEINFO_H */
