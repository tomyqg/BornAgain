// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/ParticleLayout.cpp
//! @brief     Implements class ParticleLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleLayout.h"
#include "Exceptions.h"
#include "IInterferenceFunction.h"
#include "ISampleVisitor.h"
#include "Particle.h"
#include "ParticleDistribution.h"
#include "RealParameter.h"
#include "SizeSpacingCorrelationApproximationStrategy.h"
#include <iomanip>

ParticleLayout::ParticleLayout()
    : mP_interference_function {nullptr}
    , m_total_particle_density {1.0}
{
    setName(BornAgain::ParticleLayoutType);
}

ParticleLayout::~ParticleLayout() {} // needs member class declarations => don't move to .h

ParticleLayout::ParticleLayout(const IAbstractParticle& particle)
    : mP_interference_function {nullptr}
    , m_total_particle_density {1.0}
{
    setName(BornAgain::ParticleLayoutType);
    addParticle(particle);
}

ParticleLayout::ParticleLayout(const IAbstractParticle& particle, double abundance)
    : mP_interference_function {nullptr}
    , m_total_particle_density {1.0}
{
    setName(BornAgain::ParticleLayoutType);
    addParticle(particle, abundance);
}

ParticleLayout* ParticleLayout::clone() const
{
    ParticleLayout* p_new = new ParticleLayout();

    for (size_t i = 0; i < m_particles.size(); ++i)
        p_new->addAndRegisterAbstractParticle(m_particles[i]->clone());

    if (mP_interference_function)
        p_new->setAndRegisterInterferenceFunction(mP_interference_function->clone());

    p_new->setTotalParticleSurfaceDensity(getTotalParticleSurfaceDensity());
    p_new->setApproximation(getApproximation());

    return p_new;
}

ParticleLayout* ParticleLayout::cloneInvertB() const
{
    ParticleLayout* p_new = new ParticleLayout();

    for (size_t i = 0; i < m_particles.size(); ++i)
        p_new->addAndRegisterAbstractParticle(m_particles[i]->cloneInvertB());

    if (mP_interference_function)
        p_new->setAndRegisterInterferenceFunction(mP_interference_function->clone());

    p_new->setTotalParticleSurfaceDensity(getTotalParticleSurfaceDensity());
    p_new->setApproximation(getApproximation());

    return p_new;
}

void ParticleLayout::accept(ISampleVisitor* visitor) const
{
    visitor->visit(this);
}

void ParticleLayout::addParticle(const IAbstractParticle& particle)
{
    addAndRegisterAbstractParticle(particle.clone());
}

void ParticleLayout::addParticle(const IAbstractParticle& particle, double abundance)
{
    std::unique_ptr<IAbstractParticle> P_particle_clone { particle.clone() };
    P_particle_clone->setAbundance(abundance);
    addAndRegisterAbstractParticle(P_particle_clone.release());
}

void ParticleLayout::addParticle(const IParticle& particle, double abundance,
                                 const kvector_t position)
{
    std::unique_ptr<IParticle> P_particle_clone { particle.clone() };
    P_particle_clone->setAbundance(abundance);
    if (position != kvector_t(0,0,0))
        P_particle_clone->applyTranslation(position);
    addAndRegisterAbstractParticle(P_particle_clone.release());
}

void ParticleLayout::addParticle(const IParticle& particle, double abundance,
                                 const kvector_t position, const IRotation& rotation)
{
    std::unique_ptr<IParticle> P_particle_clone { particle.clone() };
    P_particle_clone->setAbundance(abundance);
    if (!rotation.isIdentity())
        P_particle_clone->applyRotation(rotation);
    if(position != kvector_t(0,0,0))
        P_particle_clone->applyTranslation(position);
    addAndRegisterAbstractParticle(P_particle_clone.release());
}

//! Returns particle info
const IAbstractParticle* ParticleLayout::getParticle(size_t index) const
{
    if (index<m_particles.size())
        return m_particles[index];
    throw Exceptions::OutOfBoundsException(
        "ParticleLayout::getParticle() -> Error! Not so many particles in this decoration.");
}
SafePointerVector<const IParticle> ParticleLayout::getParticles() const
{
    SafePointerVector<const IParticle> particle_vector;
    for (auto particle: m_particles) {
        if (const auto* p_part_distr = dynamic_cast<const ParticleDistribution*>(particle)) {
            std::vector<const IParticle*> generated_particles;
            p_part_distr->generateParticles(generated_particles);
            for (size_t i = 0; i < generated_particles.size(); ++i) {
                particle_vector.push_back(generated_particles[i]);
            }
        } else if (const auto* p_iparticle = dynamic_cast<const IParticle*>(particle)) {
            particle_vector.push_back(p_iparticle->clone());
        }
    }
    return particle_vector;
}

double ParticleLayout::getAbundanceOfParticle(size_t index) const
{
    return m_particles[index]->getAbundance();
}

const IInterferenceFunction* ParticleLayout::getInterferenceFunction() const
{
    return mP_interference_function.get();
}

//! Adds interference functions
void ParticleLayout::addInterferenceFunction(const IInterferenceFunction& interference_function)
{
    setAndRegisterInterferenceFunction(interference_function.clone());
}

double ParticleLayout::getTotalParticleSurfaceDensity() const
{
    double iff_density =
        mP_interference_function ? mP_interference_function->getParticleDensity() : 0.0;
    return iff_density > 0.0 ? iff_density : m_total_particle_density;
}

//! Adds particle information with simultaneous registration in parent class.
void ParticleLayout::addAndRegisterAbstractParticle(IAbstractParticle* child)
{
    m_particles.push_back(child);
    registerChild(child);
}

//! Adds interference function with simultaneous registration in parent class.
void ParticleLayout::setAndRegisterInterferenceFunction(IInterferenceFunction* child)
{
    if (mP_interference_function)
        deregisterChild(mP_interference_function.get());
    mP_interference_function.reset(child);
    registerChild(child);
}

void ParticleLayout::print(std::ostream& ostr) const
{
    ILayout::print(ostr);
    ostr << "-->ParticleLayout<" << this << ">{\n";
    for( size_t i=0; i<m_particles.size(); ++i )
        ostr << "      - particle " << std::left << std::setw(2) << i << " { "
             << *(m_particles[i]) << "}\n";
    ostr << "}";
}
