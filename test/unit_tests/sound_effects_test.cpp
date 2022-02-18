#include "catch2/catch.hpp"
#include "oalpp/effects/distortion/decimator.hpp"
#include "oalpp/effects/distortion/tanh_distortion.hpp"
#include "oalpp/effects/filter/butterworth_24db_lowpass.hpp"
#include "oalpp/effects/filter/simple_highpass.hpp"
#include "oalpp/effects/filter/simple_lowpass.hpp"
#include "oalpp/effects/utility/convolution.hpp"
#include "oalpp/effects/utility/effect_chain.hpp"
#include "oalpp/effects/utility/gain.hpp"
#include "oalpp/effects/utility/phase_flip.hpp"

TEST_CASE("SoundEffect returns zero on zero input", "[SoundEffect]")
{
    SECTION("Filters")
    {
        auto const frequency = GENERATE(10.0f, 100.0f, 1000.0f, 10000.0f);
        SECTION("Butterworth24dbLopass")
        {
            auto const q = GENERATE(-0.5f, 0.0f, 0.25f, 0.5f, 0.75f, 1.0f, 1.5f);
            oalpp::effects::filter::Butterworth24dbLowpass lowpass { 44100, frequency, q };
            auto const numberOfSamples = 10000u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                REQUIRE(0 == lowpass.process(0.0f));
            }
        }

        SECTION("SimpleLowpass")
        {
            auto const r = GENERATE(0.2f, 1.0f, 1.4f);
            oalpp::effects::filter::SimpleLowpass lowpass { 44100, frequency, r };

            auto const numberOfSamples = 10000u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                REQUIRE(0 == lowpass.process(0.0f));
            }
        }

        SECTION("SimpleHighpass")
        {
            auto const r = GENERATE(0.2f, 1.0f, 1.4f);
            oalpp::effects::filter::SimpleHighpass highpass { 44100, frequency, r };

            auto const numberOfSamples = 10000u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                REQUIRE(0 == highpass.process(0.0f));
            }
        }
    }
    SECTION("Distortion")
    {
        SECTION("Tanh distortion")
        {
            auto const pregain = GENERATE(0.0f, 0.1f, 1.0f, 10.0f, 100.0f);
            oalpp::effects::distortion::TanhDistortion distortion { pregain, 1.0f };

            auto const numberOfSamples = 10000u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                REQUIRE(0.0f == distortion.process(0.0f));
            }
        }
        SECTION("decimator")
        {
            auto const bits = GENERATE(1, 2, 5, 10, 20);
            oalpp::effects::distortion::Decimator decimator { bits, 1.0f };

            auto const numberOfSamples = 10000u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                REQUIRE(0.0f == decimator.process(0.0f));
            }
        }
    }
    SECTION("utility")
    {
        SECTION("gain")
        {
            auto const gainValue = GENERATE(0.0f, 1.0f, 1000.0f, -1.0f);
            oalpp::effects::utility::Gain gain { gainValue };

            auto const numberOfSamples = 10000u;
            std::vector<float> inputVector;
            inputVector.resize(numberOfSamples);
            REQUIRE(gain.process(inputVector) == inputVector);
        }

        SECTION("effect chain")
        {
            oalpp::effects::distortion::Decimator decimator { 32, 1.0f };
            using namespace oalpp::effects::utility;
            EffectChain::EffectsT effects { decimator };
            oalpp::effects::utility::EffectChain chain { effects };

            auto const numberOfSamples = 10000u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                REQUIRE(0.0f == chain.process(0.0f));
            }
        }
    }
}

TEST_CASE("SoundEffect reset", "[SoundEffect]")
{
    SECTION("Filters")
    {
        auto const frequency = GENERATE(10.0f, 100.0f, 1000.0f, 10000.0f);
        SECTION("Butterworth24dbLopass")
        {
            auto const q = GENERATE(0.0f, 0.25f, 0.5f, 0.75f, 1.0f);
            auto const input = 1.0f;

            oalpp::effects::filter::Butterworth24dbLowpass lowpass { 44100, frequency, q };
            // process first sample
            auto const firstSampleResult = lowpass.process(input);

            // process some more samples
            auto const numberOfSamples = 3u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                lowpass.process(input);
            }

            lowpass.reset();

            REQUIRE(firstSampleResult == lowpass.process(input));
        }

        SECTION("SimpleLowpass")
        {
            auto const r = GENERATE(0.2f, 1.0f, 1.4f);
            oalpp::effects::filter::SimpleLowpass lowpass { 44100, frequency, r };
            auto const input = 1.0f;

            // process first sample
            auto const firstSampleResult = lowpass.process(input);

            // process some more samples
            auto const numberOfSamples = 3u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                lowpass.process(input);
            }

            lowpass.reset();

            REQUIRE(firstSampleResult == lowpass.process(input));
        }

        SECTION("SimpleHighpass")
        {
            auto const r = GENERATE(0.2f, 1.0f, 1.4f);
            oalpp::effects::filter::SimpleHighpass highpass { 44100, frequency, r };
            auto const input = 1.0f;

            // process first sample
            auto const firstSampleResult = highpass.process(input);

            // process some more samples
            auto const numberOfSamples = 3u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                highpass.process(input);
            }

            highpass.reset();

            REQUIRE(firstSampleResult == highpass.process(input));
        }
    }
    SECTION("Distortion")
    {
        SECTION("Tanh distortion")
        {
            oalpp::effects::distortion::TanhDistortion distortion { 1.0f, 1.0f };

            // distortion does not store any history, so reset does nothing.
            REQUIRE_NOTHROW(distortion.reset());
        }
        SECTION("decimator")
        {
            auto const bits = GENERATE(1, 2, 5, 10, 20);
            oalpp::effects::distortion::Decimator decimator { bits, 1.0f };

            auto const input = 1.0f;

            // process first sample
            auto const firstSampleResult = decimator.process(input);

            // process some more samples
            auto const numberOfSamples = 3u;
            for (auto i = 0U; i != numberOfSamples; ++i) {
                decimator.process(input);
            }

            decimator.reset();

            REQUIRE(firstSampleResult == decimator.process(input));
        }
    }
    SECTION("utility")
    {

        SECTION("effect chain")
        {
            oalpp::effects::distortion::Decimator decimator { 32, 1.0f };
            using namespace oalpp::effects::utility;
            EffectChain::EffectsT effects { decimator };
            oalpp::effects::utility::EffectChain chain { effects };

            // distortion does not store any history, so reset does nothing.
            REQUIRE_NOTHROW(chain.reset());
        }

        SECTION("phase flip")
        {
            oalpp::effects::utility::PhaseFlip flip {};

            // flip does not store any history, so reset does nothing.
            REQUIRE_NOTHROW(flip.reset());
        }
    }
}

TEST_CASE("Decimator invalid arguments", "[SoundEffect]")
{
    REQUIRE_THROWS(oalpp::effects::distortion::Decimator { 0, 1.0 });
    REQUIRE_THROWS(oalpp::effects::distortion::Decimator { 10, -1.0 });
    REQUIRE_THROWS(oalpp::effects::distortion::Decimator { 10, 1.5 });
}

TEST_CASE("Butterworth 24db lowpass invalid arguments", "[SoundEffect]")
{
    REQUIRE_THROWS(oalpp::effects::filter::Butterworth24dbLowpass { -44100, 2000.0f, 0.2f });
    REQUIRE_THROWS(oalpp::effects::filter::Butterworth24dbLowpass { 44100, -2000.0f, 0.2f });
    REQUIRE_THROWS(oalpp::effects::filter::Butterworth24dbLowpass { 44100, 192000.0f, 0.2f });
}

TEST_CASE("Simple highpass invalid arguments", "[SoundEffect]")
{
    REQUIRE_THROWS(oalpp::effects::filter::SimpleHighpass { -44100, 2000.0f, 0.2f });
    REQUIRE_THROWS(oalpp::effects::filter::SimpleHighpass { 44100, -2000.0f, 0.2f });
    REQUIRE_THROWS(oalpp::effects::filter::SimpleHighpass { 44100, 192000.0f, 0.2f });
}

TEST_CASE("Simple lowpass invalid arguments", "[SoundEffect]")
{
    REQUIRE_THROWS(oalpp::effects::filter::SimpleLowpass { -44100, 2000.0f, 0.2f });
    REQUIRE_THROWS(oalpp::effects::filter::SimpleLowpass { 44100, -2000.0f, 0.2f });
    REQUIRE_THROWS(oalpp::effects::filter::SimpleLowpass { 44100, 192000.0f, 0.2f });
}

TEST_CASE("Gain scales input audio", "[SoundEffect]")
{
    auto const gainValue = GENERATE(0.0f, 1.0f, 1000.0f, -1.0f);
    oalpp::effects::utility::Gain gain { gainValue };

    auto const inputValue = GENERATE(-1.0f, -0.5f, 0.0f, 0.5f, 1.0f);
    std::vector<float> inputVector;
    inputVector.resize(1);
    inputVector[0] = inputValue;
    REQUIRE(inputValue * gainValue == gain.process(inputVector)[0]);
}

class FakeEffect : public oalpp::effects::MonoEffectIterative {
public:
    float process(float /*unused*/) override
    {
        m_hasBeenProcessed = true;
        return m_returnValue;
    }
    void reset() override { }
    bool m_hasBeenProcessed { false };
    float m_returnValue { 0.0f };
};

TEST_CASE("EffectChain calls added effect", "[SoundEffect]")
{
    FakeEffect fake;

    using namespace oalpp::effects::utility;

    EffectChain::EffectsT effects { fake };
    oalpp::effects::utility::EffectChain chain { effects };

    chain.process(0.0f);
    REQUIRE(fake.m_hasBeenProcessed == true);
}

TEST_CASE("EffectChain returns processed sample", "[SoundEffect]")
{
    FakeEffect fake;
    fake.m_returnValue = 0.5f;

    using namespace oalpp::effects::utility;

    EffectChain::EffectsT effects { fake };
    oalpp::effects::utility::EffectChain chain { effects };

    REQUIRE(chain.process(0.0f) == 0.5f);
}

TEST_CASE("Phase flip returns inverted sample", "[SoundEffect]")
{
    oalpp::effects::utility::PhaseFlip flip {};
    float const input = GENERATE(-1.0f, -0.25f, 0.0f, 0.3f, 0.7f, 0.983f, 1.0f);
    float const expectedOutput = -input;
    float const output = flip.process(input);

    REQUIRE(output == expectedOutput);
}

TEST_CASE("Convolution with kernel of size 1 multiplies input", "[SoundEffect]")
{
    std::vector<float> kernel;
    kernel.resize(1U);
    float const kernelValue = GENERATE(-1.0f, 0.0f, 1.0f);
    kernel[0] = kernelValue;

    oalpp::effects::utility::Convolution convolution { kernel };

    float const input = GENERATE(-1.0f, -0.25f, 0.0f, 0.3f, 0.7f, 0.983f, 1.0f);
    std::vector<float> inputVector;
    inputVector.resize(1);
    inputVector[0] = input;
    std::vector<float> expectedOutputVector;
    expectedOutputVector.resize(2);
    expectedOutputVector[0] = input * kernelValue;

    std::vector<float> const output = convolution.process(inputVector);

    REQUIRE(abs(output[0] - expectedOutputVector[0]) < 0.00001);
    REQUIRE(abs(output[1] - expectedOutputVector[1]) < 0.00001);
}

TEST_CASE("Convolution with kernel of size 2 delays input", "[SoundEffect]")
{
    std::vector<float> kernel;
    kernel.resize(2U);
    float const kernelValue = GENERATE(-1.0f, 0.0f, 1.0f);
    kernel[0] = 0.0f;
    kernel[1] = kernelValue;

    oalpp::effects::utility::Convolution convolution { kernel };

    std::vector<float> inputVector;
    inputVector.resize(2);
    inputVector[0] = GENERATE(-1.0f, -0.25f, 0.0f, 0.3f, 0.7f, 0.983f, 1.0f);
    inputVector[1] = 0.0f;

    std::vector<float> expectedOutputVector;
    expectedOutputVector.resize(2);
    expectedOutputVector[0] = 0.0f;
    expectedOutputVector[1] = inputVector[0] * kernelValue;

    auto const output = convolution.process(inputVector);

    REQUIRE(abs(output[0] - expectedOutputVector[0]) < 0.00001);
    REQUIRE(abs(output[1] - expectedOutputVector[1]) < 0.00001);
}
