// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MagneticLayersBuilder.cpp
//! @brief    Implements class to build samples with magnetic layers
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/StandardSamples/MagneticLayersBuilder.h"
#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Basics/Units.h"
#include "Core/Multilayer/LayerRoughness.h"
#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/RoughnessModels.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"

MagneticSubstrateZeroFieldBuilder::MagneticSubstrateZeroFieldBuilder()
    : m_sphere_radius(5 * Units::nanometer)
{
}

MultiLayer* MagneticSubstrateZeroFieldBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    kvector_t substr_field(0.0, 0.0, 0.0);
    kvector_t particle_field(0.1, 0.0, 0.0);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 7e-6, 2e-8, substr_field);
    Material particle_material = HomogeneousMaterial("MagParticle", 6e-4, 2e-8, particle_field);

    ParticleLayout particle_layout;
    kvector_t position(0.0, 0.0, -10.0 * Units::nanometer);
    FormFactorFullSphere ff_sphere(m_sphere_radius);
    Particle particle(particle_material, ff_sphere);
    particle_layout.addParticle(particle, 1.0, position);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);
    substrate_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

SimpleMagneticLayerBuilder::SimpleMagneticLayerBuilder() = default;

MultiLayer* SimpleMagneticLayerBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    kvector_t layer_field = kvector_t(0.0, 1e8, 0.0);
    Material air_material = MaterialBySLD("Air", 0.0, 0.0);
    Material layer_material = MaterialBySLD("MagLayer", 1e-4, 1e-8, layer_field);
    Material substrate_material = MaterialBySLD("Substrate", 7e-5, 2e-6);

    Layer air_layer(air_material);
    Layer intermediate_layer(layer_material, 10.0); // 10 nm layer thickness
    Layer substrate_layer(substrate_material);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(intermediate_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

MagneticLayerBuilder::MagneticLayerBuilder() : m_sphere_radius(5 * Units::nanometer) {}

MultiLayer* MagneticLayerBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    kvector_t layer_field = kvector_t(0.0, 0.0, 1e6);
    kvector_t particle_field(1e6, 0.0, 0.0);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material layer_material = HomogeneousMaterial("Air", 0.0, 0.0, layer_field);
    Material substrate_material = HomogeneousMaterial("Substrate", 7e-6, 2e-8);
    Material particle_material = HomogeneousMaterial("MagParticle", 6e-4, 2e-8, particle_field);

    ParticleLayout particle_layout;
    FormFactorFullSphere ff_sphere(m_sphere_radius);
    Particle particle(particle_material, ff_sphere);
    particle_layout.addParticle(particle, 1.0);

    Layer air_layer(air_material);
    Layer intermediate_layer(layer_material);
    intermediate_layer.addLayout(particle_layout);
    Layer substrate_layer(substrate_material);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(intermediate_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}

SimpleMagneticRotationBuilder::SimpleMagneticRotationBuilder() = default;

MultiLayer* SimpleMagneticRotationBuilder::buildSample() const
{
    return builder();
}

MultiLayer* SimpleMagneticRotationBuilder::builder(double sigmaRoughness,
                                                  RoughnessModel roughnessModel) const
{
    MultiLayer* multi_layer = new MultiLayer();

    kvector_t substr_field = kvector_t(0.0, 1e6, 0.0);
    kvector_t layer_field = kvector_t(1e6, 1e6, 0.0);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 7e-6, 2e-8, substr_field);
    Material layer_material = HomogeneousMaterial("MagLayer", 6e-4, 2e-8, layer_field);

    auto roughness = LayerRoughness();
    roughness.setSigma(sigmaRoughness * Units::angstrom);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);
    Layer layer(layer_material, 200*Units::angstrom);
    multi_layer->addLayer(air_layer);
    multi_layer->addLayerWithTopRoughness(layer, roughness);
    multi_layer->addLayerWithTopRoughness(substrate_layer, roughness);
    multi_layer->setRoughnessModel(roughnessModel);
    return multi_layer;
}

size_t SimpleMagneticRotationBuilder::size(){return 3;}

MultiLayer* SimpleMagneticRotationBuilder::createSample(size_t index)
{

    switch(index){

        case 0:
            return builder(0.);

        case 1:
            setName("Tanh");
            return builder(2., RoughnessModel::TANH);

        case 2:
            setName("NC");
            return builder(2., RoughnessModel::NEVOT_CROCE);

        default:
            throw std::runtime_error("SimpleMagneticRotationBuilder::createSample() -> Error. "
                                 "Sample index is out of range.");
    }

}


MagneticRotationBuilder::MagneticRotationBuilder() : m_sphere_radius(5 * Units::nanometer) {}

MultiLayer* MagneticRotationBuilder::buildSample() const
{
    MultiLayer* multi_layer = new MultiLayer();

    kvector_t substr_field = kvector_t(0.0, 1e6, 0.0);
    kvector_t particle_field(1e6, 0.0, 0.0);
    Material air_material = HomogeneousMaterial("Air", 0.0, 0.0);
    Material substrate_material = HomogeneousMaterial("Substrate", 7e-6, 2e-8, substr_field);
    Material particle_material = HomogeneousMaterial("MagParticle", 6e-4, 2e-8, particle_field);

    ParticleLayout particle_layout;
    kvector_t position(0.0, 0.0, -10.0 * Units::nanometer);
    FormFactorFullSphere ff_sphere(m_sphere_radius);
    Particle particle(particle_material, ff_sphere);
    RotationZ rot_z(90 * Units::deg);
    particle_layout.addParticle(particle, 1.0, position, rot_z);

    Layer air_layer(air_material);
    Layer substrate_layer(substrate_material);
    substrate_layer.addLayout(particle_layout);

    multi_layer->addLayer(air_layer);
    multi_layer->addLayer(substrate_layer);
    return multi_layer;
}
