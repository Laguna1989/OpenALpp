#include "catch2/catch.hpp"
#include "oalpp/sound_data/sound_data_mono_to_stereo.hpp"
#include "sound_data_fake.hpp"

using namespace oalpp;

TEST_CASE("SoundDataMonoToStereo", "[SoundConversion, SoundDataMonoToStereo]")
{
    SoundDataMonoFake fake {};

    SECTION("Correct number of channels")
    {
        SoundDataMonoToStereo stereo { fake };
        REQUIRE(stereo.getNumberOfChannels() == 2);
    }

    SECTION("Same sample rate as original")
    {
        SoundDataMonoToStereo stereo { fake };
        REQUIRE(stereo.getSampleRate() == fake.getSampleRate());
    }

    SECTION("Correct samples after conversion")
    {
        fake.m_samples = std::vector<float> { 1.0f, 2.0f, 3.0f, 4.0f };
        std::vector<float> const expected_result { 1.0f, 1.0f, 2.0f, 2.0f, 3.0f, 3.0f, 4.0f, 4.0f };
        SoundDataMonoToStereo stereo { fake };

        REQUIRE(expected_result == stereo.getSamples());
    }

    SECTION("Raises exception on stereo data")
    {
        SoundDataStereoFake fakeStereo {};
        REQUIRE_THROWS(SoundDataMonoToStereo { fakeStereo });
    }
}
