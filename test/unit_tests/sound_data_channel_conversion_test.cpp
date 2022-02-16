#include "catch2/catch.hpp"
#include "oalpp/sound_data/sound_data_left_to_mono.hpp"
#include "oalpp/sound_data/sound_data_mid_to_mono.hpp"
#include "oalpp/sound_data/sound_data_mono_to_stereo.hpp"
#include "oalpp/sound_data/sound_data_right_to_mono.hpp"
#include "oalpp/sound_data/sound_data_side_to_mono.hpp"
#include "sound_data_fake.hpp"

using namespace oalpp;

TEST_CASE("SoundDataMonoToStereo", "[SoundConversion]")
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

TEST_CASE("SoundDataLeftToMono", "[SoundConversion]")
{
    SoundDataStereoFake fake {};

    SECTION("Correct number of channels")
    {
        SoundDataLeftToMono mono { fake };
        REQUIRE(mono.getNumberOfChannels() == 1);
    }

    SECTION("Same sample rate as original")
    {
        SoundDataLeftToMono mono { fake };
        REQUIRE(mono.getSampleRate() == fake.getSampleRate());
    }

    SECTION("Correct samples after conversion")
    {
        fake.m_samples = std::vector<float> { 1.0f, 2.0f, 3.0f, 4.0f };
        std::vector<float> const expected_result { 1.0f, 3.0f };
        SoundDataLeftToMono mono { fake };

        REQUIRE(expected_result == mono.getSamples());
    }

    SECTION("Raises exception on mono data")
    {
        SoundDataMonoFake fakeStereo {};
        REQUIRE_THROWS(SoundDataLeftToMono { fakeStereo });
    }
}

TEST_CASE("SoundDataRightToMono", "[SoundConversion]")
{
    SoundDataStereoFake fake {};

    SECTION("Correct number of channels")
    {
        SoundDataRightToMono mono { fake };
        REQUIRE(mono.getNumberOfChannels() == 1);
    }

    SECTION("Same sample rate as original")
    {
        SoundDataRightToMono mono { fake };
        REQUIRE(mono.getSampleRate() == fake.getSampleRate());
    }

    SECTION("Correct samples after conversion")
    {
        fake.m_samples = std::vector<float> { 1.0f, 2.0f, 3.0f, 4.0f };
        std::vector<float> const expected_result { 2.0f, 4.0f };
        SoundDataRightToMono mono { fake };

        REQUIRE(expected_result == mono.getSamples());
    }

    SECTION("Raises exception on mono data")
    {
        SoundDataMonoFake fakeStereo {};
        REQUIRE_THROWS(SoundDataLeftToMono { fakeStereo });
    }
}

TEST_CASE("SoundDataMidToMono", "[SoundConversion]")
{
    SoundDataStereoFake fake {};

    SECTION("Correct number of channels")
    {
        SoundDataMidToMono mono { fake };
        REQUIRE(mono.getNumberOfChannels() == 1);
    }

    SECTION("Same sample rate as original")
    {
        SoundDataMidToMono mono { fake };
        REQUIRE(mono.getSampleRate() == fake.getSampleRate());
    }

    SECTION("Correct samples after conversion")
    {
        fake.m_samples = std::vector<float> { 1.0f, 2.0f, 3.0f, 4.0f };
        std::vector<float> const expected_result { 1.5f, 3.5f };
        SoundDataMidToMono mono { fake };

        REQUIRE(expected_result == mono.getSamples());
    }

    SECTION("Raises exception on mono data")
    {
        SoundDataMonoFake fakeStereo {};
        REQUIRE_THROWS(SoundDataLeftToMono { fakeStereo });
    }
}

TEST_CASE("SoundDataSideToMono", "[SoundConversion]")
{
    SoundDataStereoFake fake {};

    SECTION("Correct number of channels")
    {
        SoundDataSideToMono mono { fake };
        REQUIRE(mono.getNumberOfChannels() == 1);
    }

    SECTION("Same sample rate as original")
    {
        SoundDataSideToMono mono { fake };
        REQUIRE(mono.getSampleRate() == fake.getSampleRate());
    }

    SECTION("Correct samples after conversion")
    {
        fake.m_samples = std::vector<float> { 1.0f, 2.0f, 3.0f, 4.0f };
        std::vector<float> const expected_result { -0.5f, -0.5f };
        SoundDataSideToMono mono { fake };

        REQUIRE(expected_result == mono.getSamples());
    }

    SECTION("Raises exception on mono data")
    {
        SoundDataMonoFake fakeStereo {};
        REQUIRE_THROWS(SoundDataLeftToMono { fakeStereo });
    }
}
