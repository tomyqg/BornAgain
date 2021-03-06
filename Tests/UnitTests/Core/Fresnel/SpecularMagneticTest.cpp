#include "Core/Basics/Units.h"
#include "Core/Computation/ProcessedSample.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/SpecularMagneticStrategy.h"
#include "Core/Multilayer/SpecularMagneticNewTanhStrategy.h"
#include "Core/Multilayer/SpecularScalarTanhStrategy.h"
#include "Core/Parametrization/SimulationOptions.h"
#include "Tests/GTestWrapper/google_test.h"
#include <utility>

constexpr double eps = 1e-10;

class SpecularMagneticTest : public ::testing::Test
{
protected:
    std::pair<std::unique_ptr<ProcessedSample>, std::unique_ptr<ProcessedSample>>
    sample_zerofield();

    std::unique_ptr<ProcessedSample> sample_degenerate();
    //! Compares results with scalar case
    template<typename Strategy>
    void testZeroField(const kvector_t& k, const ProcessedSample& m_layer_scalar,
                       const ProcessedSample& m_layer_zerofield);
    template<typename Strategy> void testcase_zerofield();

    template<typename Strategy>
    void test_degenerate();

    void ifEqual(const Eigen::Vector2cd& lhs, const Eigen::Vector2cd& rhs);
};

void SpecularMagneticTest::ifEqual(const Eigen::Vector2cd& lhs, const Eigen::Vector2cd& rhs)
{
    EXPECT_NEAR(0.0, std::abs(lhs(0) - rhs(0)), eps);
    EXPECT_NEAR(0.0, std::abs(lhs(1) - rhs(1)), eps);
}

template<typename Strategy>
void SpecularMagneticTest::test_degenerate()
{
    kvector_t v;

    Eigen::Vector2cd Tp_ref{0.5, 0.0};
    Eigen::Vector2cd Rp_ref{-0.5, 0.0};
    Eigen::Vector2cd Tm_ref{0.0, 0.5};
    Eigen::Vector2cd Rm_ref{0.0, -0.5};

    auto sample = sample_degenerate();
    auto result = std::make_unique<Strategy>()->Execute(sample->slices(), v);
    for (auto& coeff : result) {
        ifEqual(coeff->T1plus(), Tp_ref);
        ifEqual(coeff->T2plus(), Tp_ref);
        ifEqual(coeff->T1min(), Tm_ref);
        ifEqual(coeff->T2min(), Tm_ref);
        ifEqual(coeff->R1plus(), Rp_ref);
        ifEqual(coeff->R2plus(), Rp_ref);
        ifEqual(coeff->R1min(), Rm_ref);
        ifEqual(coeff->R2min(), Rm_ref);
    }
}

template<typename Strategy>
void SpecularMagneticTest::testZeroField(const kvector_t& k,
                                         const ProcessedSample& sample_scalar,
                                         const ProcessedSample& sample_zerofield)
{
    auto coeffs_scalar =
        std::make_unique<SpecularScalarTanhStrategy>()->Execute(sample_scalar.slices(), k);
    auto coeffs_zerofield =
        std::make_unique<Strategy>()->Execute(sample_zerofield.slices(), k);

    EXPECT_EQ(coeffs_scalar.size(), coeffs_zerofield.size());

    for (size_t i = 0; i < coeffs_scalar.size(); ++i) {
        const ScalarRTCoefficients& RTScalar =
            *dynamic_cast<const ScalarRTCoefficients*>(coeffs_scalar[i].get());
        Eigen::Vector2cd TPS = RTScalar.T1plus() + RTScalar.T2plus();
        Eigen::Vector2cd RPS = RTScalar.R1plus() + RTScalar.R2plus();
        Eigen::Vector2cd TMS = RTScalar.T1min() + RTScalar.T2min();
        Eigen::Vector2cd RMS = RTScalar.R1min() + RTScalar.R2min();

        auto& RTMatrix =
            *dynamic_cast<const typename Strategy::coefficient_type*>(coeffs_zerofield[i].get());
        Eigen::Vector2cd TPM = RTMatrix.T1plus() + RTMatrix.T2plus();
        Eigen::Vector2cd RPM = RTMatrix.R1plus() + RTMatrix.R2plus();
        Eigen::Vector2cd TMM = RTMatrix.T1min() + RTMatrix.T2min();
        Eigen::Vector2cd RMM = RTMatrix.R1min() + RTMatrix.R2min();

        ifEqual(TPS, TPM);
        ifEqual(RPS, RPM);
        ifEqual(TMS, TMM);
        ifEqual(RMS, RMM);

        ifEqual(RTScalar.getKz(), RTMatrix.getKz());
    }
}

std::unique_ptr<ProcessedSample> SpecularMagneticTest::sample_degenerate()
{
    MultiLayer mLayer;
    Material air = HomogeneousMaterial("air", 0, 1.0);
    mLayer.addLayer(Layer(air, 0 * Units::nanometer));
    return std::make_unique<ProcessedSample>(mLayer, SimulationOptions());
}

TEST_F(SpecularMagneticTest, degenerate)
{
    test_degenerate<SpecularMagneticStrategy>();
}

TEST_F(SpecularMagneticTest, degenerate_new)
{
    test_degenerate<SpecularMagneticNewTanhStrategy>();
}

std::pair<std::unique_ptr<ProcessedSample>, std::unique_ptr<ProcessedSample>>
SpecularMagneticTest::sample_zerofield()
{
    kvector_t substr_field(0.0, 0.0, 0.0);

    MultiLayer multi_layer_scalar;
    Material substr_material_scalar = HomogeneousMaterial("Substrate", 7e-6, 2e-8);
    Layer air_layer(HomogeneousMaterial("Air", 0.0, 0.0));
    Layer substr_layer_scalar(substr_material_scalar);
    multi_layer_scalar.addLayer(air_layer);
    multi_layer_scalar.addLayer(substr_layer_scalar);
    std::vector<ScalarRTCoefficients> coeffs_scalar;

    MultiLayer multi_layer_zerofield;
    Material substr_material_zerofield = HomogeneousMaterial("Substrate", 7e-6, 2e-8, substr_field);
    Layer substr_layer_zerofield(substr_material_zerofield);
    multi_layer_zerofield.addLayer(air_layer);
    multi_layer_zerofield.addLayer(substr_layer_zerofield);

    SimulationOptions options;
    auto sample_scalar = std::make_unique<ProcessedSample>(multi_layer_scalar, options);
    auto sample_zerofield = std::make_unique<ProcessedSample>(multi_layer_zerofield, options);

    return std::make_pair(std::move(sample_scalar), std::move(sample_zerofield));
}

template<typename Strategy>
void SpecularMagneticTest::testcase_zerofield()
{
    kvector_t k1 = vecOfLambdaAlphaPhi(1.0, -0.1 * Units::deg, 0.0);
    kvector_t k2 = vecOfLambdaAlphaPhi(1.0, -2.0 * Units::deg, 0.0);
    kvector_t k3 = vecOfLambdaAlphaPhi(1.0, -10.0 * Units::deg, 0.0);

    auto samples = sample_zerofield();

    testZeroField<Strategy>(k1, *std::get<0>(samples), *std::get<1>(samples));
    testZeroField<Strategy>(k2, *std::get<0>(samples), *std::get<1>(samples));
    testZeroField<Strategy>(k3, *std::get<0>(samples), *std::get<1>(samples));
}

TEST_F(SpecularMagneticTest, zerofield)
{
    testcase_zerofield<SpecularMagneticStrategy>();
}

TEST_F(SpecularMagneticTest, zerofield_new)
{
    testcase_zerofield<SpecularMagneticNewTanhStrategy>();
}
