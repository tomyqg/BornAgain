// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/SelfConsistenceTest/SelfConsistenceTest.cpp
//! @brief     Implements class SelfConsistenceTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/SelfConsistenceTest/SelfConsistenceTest.h"
#include "BATesting.h"
#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Simulation/Simulation.h"
#include "Core/Tools/FileSystemUtils.h"
#include "Tests/Functional/TestMachinery/TestUtils.h"
#include <cassert>

namespace
{
std::string composeName(std::string d_name, std::string test_name, size_t index);
}

SelfConsistenceTest::SelfConsistenceTest(const std::string& name, const std::string& description,
                                         std::vector<std::unique_ptr<Simulation>> simulations,
                                         double threshold)
    : IFunctionalTest(name, description), m_simulations(std::move(simulations)),
      m_threshold(threshold)
{
    assert(m_simulations.size()>=2); // need at least two simulations to compare
}

bool SelfConsistenceTest::runTest()
{
    // Run simulation.
    std::vector<std::unique_ptr<OutputData<double>>> results;
    for (auto& simulation : m_simulations) {
        simulation->runSimulation();
        auto sim_result = simulation->result();
        results.push_back(sim_result.data());
    }

    // Compare with reference if available.
    bool success = true;
    for (size_t i = 1, size = results.size(); i < size; ++i) {
        const bool outcome = TestUtils::isTheSame(*results[i], *results[0], m_threshold);
        if (!outcome) { // compose message and save results
            std::stringstream ss;
            ss << "Simulations 0 and " << i << " yield different results.\n"
               << "Results are stored in\n";
            const std::string output_dname = BATesting::SelfConsistenceOutputDir();
            FileSystemUtils::createDirectories(output_dname);
            for (size_t index : {size_t(0), i}) {
                const std::string fname = composeName(output_dname, getName(), index);
                IntensityDataIOFactory::writeOutputData(*results[index], fname);
                ss << "- " << fname << "\n";
            }
            std::cout << ss.str();
        }
        success = success && outcome;
    }

    if (!success)
        std::cout << "Test " << getName() << " failed." << std::endl;
    return success;
}

namespace
{
std::string composeName(std::string d_name, std::string test_name, size_t index)
{
    std::stringstream ss;
    ss << index;
    return FileSystemUtils::jointPath(d_name, test_name + ss.str() + ".int.gz");
}
} // namespace
