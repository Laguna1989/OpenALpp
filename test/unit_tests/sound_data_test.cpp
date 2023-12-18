#include <catch2/catch.hpp>
#include <oalpp/sound_data/sound_data.hpp>

TEST_CASE("SoundData Move constructor", "[SoundData]")
{
    oalpp::SoundData data1 { std::vector<float> { 1.0f, 2.0f }, 44100, 2 };
    oalpp::SoundData data2 { std::move(data1) };
    REQUIRE(data2.getSamples().size() == 2);
    REQUIRE(data2.getSamples().at(0) == 1.0f);
    REQUIRE(data2.getSamples().at(1) == 2.0f);

    REQUIRE(data2.getSampleRate() == 44100);
    REQUIRE(data2.getNumberOfChannels() == 2);
}

TEST_CASE("SoundData Move assignment operator", "[SoundData]")
{
    oalpp::SoundData data1 { std::vector<float> { 1.0f, 2.0f }, 44100, 2 };
    oalpp::SoundData data2 = std::move(data1);

    REQUIRE(data2.getSamples().size() == 2);
    REQUIRE(data2.getSamples().at(0) == 1.0f);
    REQUIRE(data2.getSamples().at(1) == 2.0f);

    REQUIRE(data2.getSampleRate() == 44100);
    REQUIRE(data2.getNumberOfChannels() == 2);
}
