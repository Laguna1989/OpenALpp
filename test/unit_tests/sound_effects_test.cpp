#include "catch2/catch.hpp"
#include "oalpp/effects/distortion/decimator.hpp"
#include "oalpp/effects/distortion/tanh_distortion.hpp"
#include "oalpp/effects/filter/butterworth_24db_lowpass.hpp"
#include "oalpp/effects/filter/simple_highpass.hpp"
#include "oalpp/effects/filter/simple_lowpass.hpp"

TEST_CASE("SoundEffect returns zero on zero input", "[SoundEffect]")
{
    SECTION("Filters")
    {
        auto frequency = GENERATE(1.0f, 10.0f, 100.0f, 1000.0f, 10000.0f);
        SECTION("Butterworth24dbLopass")
        {
            auto const q = GENERATE(0.0f, 0.25f, 0.5f, 0.75f, 1.0f);
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
}
