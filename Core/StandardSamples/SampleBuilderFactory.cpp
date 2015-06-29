// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/SampleBuilderFactory.cpp
//! @brief     Implement class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleBuilderFactory.h"
#include "CylindersAndPrismsBuilder.h"
#include "CylindersBuilder.h"
#include "ParaCrystalBuilder.h"
#include "TwoDimLatticeBuilder.h"
#include "CustomMorphologyBuilder.h"
#include "RotatedPyramidsBuilder.h"
#include "CoreShellParticleBuilder.h"
#include "ParticlesInSSCABuilder.h"
#include "MesoCrystalBuilder.h"
#include "MultipleLayoutBuilder.h"
#include "PolarizedDWBAMagCylindersBuilder.h"
#include "MultiLayerWithRoughnessBuilder.h"
#include "ParticleCompositionBuilder.h"
#include "ParticleInTheAirBuilder.h"
#include "ParticleDistributionsBuilder.h"
#include "RipplesBuilder.h"

SampleBuilderFactory::SampleBuilderFactory()
{
    registerItem(
        "CylindersAndPrismsBuilder",
        IFactoryCreateFunction<CylindersAndPrismsBuilder, ISampleBuilder>,
        "Mixture of cylinders and prisms without interference");

    registerItem(
        "TwoTypesCylindersDistributionBuilder",
        IFactoryCreateFunction<TwoTypesCylindersDistributionBuilder, ISampleBuilder>,
        "Mixture of cylinder particles with two types size distribution ");

    registerItem(
        "CylindersInBABuilder",
        IFactoryCreateFunction<CylindersInBABuilder, ISampleBuilder>,
        "Cylinder formfactor in BA");
    registerItem(
        "CylindersInDWBABuilder",
        IFactoryCreateFunction<CylindersInDWBABuilder, ISampleBuilder>,
        "Cylinder formfactor in DWBA");

    registerItem(
        "CylindersWithSizeDistributionBuilder",
        IFactoryCreateFunction<CylindersWithSizeDistributionBuilder, ISampleBuilder>,
        "Cylinder formfactor in BA with size distribution");

    registerItem(
        "RadialParaCrystalBuilder",
        IFactoryCreateFunction<RadialParaCrystalBuilder, ISampleBuilder>,
        "Interference function of radial paracrystal");

    registerItem(
        "HexParaCrystalBuilder",
        IFactoryCreateFunction<HexParaCrystalBuilder, ISampleBuilder>,
        "Interference function of 2D hexagonal paracrystal");

    registerItem(
        "RectParaCrystalBuilder",
        IFactoryCreateFunction<RectParaCrystalBuilder, ISampleBuilder>,
        "Interference function of 2D rectangular paracrystal");

    registerItem(
        "SquareLatticeBuilder",
        IFactoryCreateFunction<SquareLatticeBuilder, ISampleBuilder>,
        "Interference of square lattice with disordered");

    registerItem(
        "CenteredSquareLatticeBuilder",
        IFactoryCreateFunction<CenteredSquareLatticeBuilder, ISampleBuilder>,
        "Interference of centered square lattice");

    registerItem(
        "RotatedSquareLatticeBuilder",
        IFactoryCreateFunction<RotatedSquareLatticeBuilder, ISampleBuilder>,
        "2D lattice rotated");

    registerItem(
        "CustomRotatedLatticeBuilder",
        IFactoryCreateFunction<CustomRotatedLatticeBuilder, ISampleBuilder>,
        "2D lattice variants");

    registerItem(
        "CustomMorphologyBuilder",
        IFactoryCreateFunction<CustomMorphologyBuilder, ISampleBuilder>,
        "Mixture of different particles a la IsGISAXS morphology file");

//    registerItem(
//        "isgisaxs08a",
//        IFactoryCreateFunction<RectParaCrystalBuilder, ISampleBuilder>,
//        "2DDL paracrystal lattice");

//    registerItem(
//        "isgisaxs08b",
//        IFactoryCreateFunction<IsGISAXS08BBuilder, ISampleBuilder>,
//        "2D paracrystal lattice with isotropic pdfs");

    registerItem(
        "RotatedPyramidsBuilder",
        IFactoryCreateFunction<RotatedPyramidsBuilder, ISampleBuilder>,
        "Rotated pyramids on top of substrate");

//    registerItem(
//        "isgisaxs10",
//        IFactoryCreateFunction<IsGISAXS10Builder, ISampleBuilder>,
//        "Cylinders on top of substrate with interference");

    registerItem(
        "CoreShellParticleBuilder",
        IFactoryCreateFunction<CoreShellParticleBuilder, ISampleBuilder>,
        "Core shell nanoparticles");

    registerItem(
        "ParticlesInSSCABuilder",
        IFactoryCreateFunction<ParticlesInSSCABuilder, ISampleBuilder>,
        "Size spacing correlation approximation");

    registerItem(
        "MesoCrystalBuilder",
        IFactoryCreateFunction<MesoCrystalBuilder, ISampleBuilder>,
        "Mesocrystals of cylindrical shape composed by spherical nanoparticles");

    registerItem(
        "MagneticParticleZeroFieldBuilder",
        IFactoryCreateFunction<MagneticParticleZeroFieldBuilder, ISampleBuilder>,
        "Polarized DWBA with zero magnetic field");

    registerItem(
        "polmagcylinders2",
        IFactoryCreateFunction<PolarizedDWBAMagCylinders2Builder, ISampleBuilder>,
        "Polarized DWBA with non-zero magnetic field");

    registerItem(
        "MultiLayerWithRoughnessBuilder",
        IFactoryCreateFunction<MultiLayerWithRoughnessBuilder, ISampleBuilder>,
        "Layer with correlated roughness");

    registerItem(
       "MultipleLayoutBuilder",
       IFactoryCreateFunction<MultipleLayoutBuilder, ISampleBuilder>,
      "cylinder and prisms using multiple layouts");

    registerItem(
        "TriangularRippleBuilder",
        IFactoryCreateFunction<TriangularRippleBuilder, ISampleBuilder>,
        "triangular ripple within the 1D-paracrystal model");

    registerItem(
        "CosineRippleBuilder",
        IFactoryCreateFunction<CosineRippleBuilder, ISampleBuilder>,
        "cosine ripple within the 1D-paracrystal model");

    registerItem(
        "ParticleCompositionBuilder",
        IFactoryCreateFunction<ParticleCompositionBuilder, ISampleBuilder>,
        "Composition of particles to represent two layers of spheres in hex lattice");

    registerItem(
        "ParticleInTheAirBuilder",
        IFactoryCreateFunction<ParticleInTheAirBuilder, ISampleBuilder>,
        "Particle in the air layer to test form factors");

}


ISample *SampleBuilderFactory::createSample(const std::string& name)
{
    SampleBuilder_t builder(createItem(name));
    ISample *result = builder->buildSample();
    result->setName(name);
    return result;
}


SampleBuilder_t SampleBuilderFactory::createBuilder(const std::string& name)
{
    SampleBuilder_t result(createItem(name));
    result->setName(name);
    return result;
}
