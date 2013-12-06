#include "IsGISAXS041DDL.h"
#include "OutputDataIOFactory.h"
#include "SampleBuilderFactory.h"
#include "Simulation.h"
#include "Units.h"
#include "Utils.h"
#include "MathFunctions.h"
#include "SimulationRegistry.h"
#include "OutputDataFunctions.h"
#include <iostream>
#include <cmath>
#include <gsl/gsl_errno.h>

FunctionalTests::IsGISAXS041DDL::IsGISAXS041DDL()
    : m_name("IsGISAXS041DDL")
    , m_description("1D Paracrystal")
    , m_result(0)
	, m_reference(0)
{ }


void FunctionalTests::IsGISAXS041DDL::run(const std::string &path_to_data)
{

    SimulationRegistry sim_registry;
    Simulation *simulation = sim_registry.createSimulation("isgisaxs04_1DDL");

    // loading reference data
    std::string filename = path_to_data + "isgisaxs04_reference_1DDL.ima.gz";
    m_reference = OutputDataIOFactory::readIntensityData(filename);

    simulation->runSimulation();

    m_result = simulation->getIntensityData();
    delete simulation;
}


int FunctionalTests::IsGISAXS041DDL::analyseResults()
{
    const double threshold(2e-10);

    // Calculating average relative difference.
    double diff = OutputDataFunctions::GetDifference(*m_result,*m_reference);

    // Assess result.
	bool status_ok(true);
    if( diff > threshold ) status_ok=false;

    std::cout << " diff " << diff << std::endl;
    std::cout << m_name << " " << m_description << " " <<
            (status_ok ? "[OK]" : "[FAILED]") << std::endl;
    return (status_ok ? 0 : 1);
}


#ifdef STANDALONE
std::string GetPathToData(int argc, char **argv)
{
    if(argc == 2) return argv[1];
    return Utils::FileSystem::GetPathToData("../../../ReferenceData/BornAgain/", argv[0]);
}

int main(int argc, char **argv)
{
    FunctionalTests::IsGISAXS041DDL test;
    test.run(GetPathToData(argc, argv));
    return test.analyseResults();
}
#endif
