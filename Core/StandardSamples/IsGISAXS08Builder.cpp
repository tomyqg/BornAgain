#include "IsGISAXS08Builder.h"
#include "MultiLayer.h"
#include "ParticleDecoration.h"
#include "MaterialManager.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "FormFactorCylinder.h"
#include "Units.h"
#include "ParticleBuilder.h"

IsGISAXS08Para1DBuilder::IsGISAXS08Para1DBuilder()
{
}

ISample *IsGISAXS08Para1DBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

	complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    InterferenceFunction2DParaCrystal *p_interference_function =
            new InterferenceFunction2DParaCrystal(10.0*Units::nanometer,
                    10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
    p_interference_function->setDomainSizes(20.0*Units::micrometer,
            20.0*Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 2.0*Units::nanometer);
    FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 2.0*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf1, pdf2);
    ParticleDecoration particle_decoration( new Particle(particle_material,
            new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}


// -----------------------------------------------------------------------------
//

IsGISAXS08Para2DBuilder::IsGISAXS08Para2DBuilder()
{
}

// IsGISAXS8 functional test: 2D paracrystal lattice with isotropic pdfs
ISample *IsGISAXS08Para2DBuilder::buildSample() const
{
    MultiLayer *multi_layer = new MultiLayer();

    complex_t n_particle(1.0-6e-4, 2e-8);
    const IMaterial *p_air_material =
            MaterialManager::getHomogeneousMaterial("Air", 0.0, 0.0);
    const IMaterial *p_substrate_material =
            MaterialManager::getHomogeneousMaterial("Substrate", 6e-6, 2e-8);
    const IMaterial *particle_material =
            MaterialManager::getHomogeneousMaterial("Particle", n_particle);

    Layer air_layer;
    air_layer.setMaterial(p_air_material);
    Layer substrate_layer;
    substrate_layer.setMaterial(p_substrate_material);

    InterferenceFunction2DParaCrystal *p_interference_function =
            new InterferenceFunction2DParaCrystal(10.0*Units::nanometer,
                    10.0*Units::nanometer, M_PI/2.0, 0.0, 0.0);
    p_interference_function->setDomainSizes(20.0*Units::micrometer,
            20.0*Units::micrometer);
    FTDistribution2DCauchy pdf1(0.5*Units::nanometer, 0.5*Units::nanometer);
    FTDistribution2DCauchy pdf2(0.5*Units::nanometer, 0.5*Units::nanometer);
    p_interference_function->setProbabilityDistributions(pdf1, pdf2);
    ParticleDecoration particle_decoration( new Particle(particle_material,
            new FormFactorCylinder(5*Units::nanometer, 5*Units::nanometer)));
    particle_decoration.addInterferenceFunction(p_interference_function);

    air_layer.setDecoration(particle_decoration);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);

    return multi_layer;
}