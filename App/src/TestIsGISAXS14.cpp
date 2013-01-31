#include "TestIsGISAXS14.h"
#include "IsGISAXSTools.h"
#include "OutputDataIOFactory.h"
#include "Utils.h"

#include "GISASExperiment.h"
#include "MultiLayer.h"
#include "SampleFactory.h"
#include "Units.h"

#include <fstream>


TestIsGISAXS14::TestIsGISAXS14() : IFunctionalTest("TestIsGISAXS14")
{
    setOutputPath(Utils::FileSystem::GetHomePath()+"./Examples/IsGISAXS_examples/ex-14/" );
}


void TestIsGISAXS14::execute()
{
    MultiLayer *sample = dynamic_cast<MultiLayer *>(SampleFactory::instance().createItem("IsGISAXS14_LayeredSpheresOnGradedInterface"));

    GISASExperiment experiment(mp_options);
    experiment.setSample(*sample);
    experiment.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree, 100, 0.0*Units::degree, 2.0*Units::degree, true);
    experiment.setBeamParameters(1.0*Units::angstrom, -0.2*Units::degree, 0.0*Units::degree);
    experiment.runSimulation();
    OutputDataIOFactory::writeOutputData(*experiment.getOutputDataClone(), getOutputPath() + "this_multilayer_sphere.ima");
}


void TestIsGISAXS14::finalise()
{
    std::string isgi_file(getOutputPath()+"isgi_normal_sphere.ima");
    std::string this_file(getOutputPath()+"this_multilayer_sphere.ima");

    OutputData<double> *isgi_data = OutputDataIOFactory::getOutputData(isgi_file);
    OutputData<double> *our_data = OutputDataIOFactory::getOutputData(this_file);

    IsGISAXSTools::drawOutputDataComparisonResults(*our_data, *isgi_data, "TestIsGISAXS14_c1", "Multilayered sphere on graded interface");

    delete isgi_data;
    delete our_data;
}