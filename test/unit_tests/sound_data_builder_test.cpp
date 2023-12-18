#include <catch2/catch.hpp>
#include <oalpp/effects/utility/effect_chain.hpp>
#include <oalpp/effects/utility/gain.hpp>
#include <oalpp/sound_data/sound_data.hpp>
#include <oalpp/sound_data/sound_data_builder.hpp>
#include <libnyquist/Decoders.h>

TEST_CASE("SoundDataBuilder", "[SoundDataBuilder]")
{
    oalpp::SoundDataBuilder builder {};

    SECTION("With Default Builder")
    {
        SECTION("Creates empty SoundData")
        {
            auto const data = builder.create();
            REQUIRE(data.getNumberOfChannels() == 0);
            REQUIRE(data.getSampleRate() == 0);
            REQUIRE(data.getSamples().empty());
        }
        SECTION("OnlyLeftChannel raises Exception") { REQUIRE_THROWS(builder.onlyLeftChannel()); }
        SECTION("OnlyRightChannel raises Exception") { REQUIRE_THROWS(builder.onlyRightChannel()); }
        SECTION("MonoToStereo raises Exception") { REQUIRE_THROWS(builder.toStereo()); }
    }

    SECTION("With Stereo file")
    {
        nqr::NyquistIO loader;
        auto const fileData = std::make_unique<nqr::AudioData>();
        loader.Load(fileData.get(), "assets/test.mp3");
        auto samples_expected = std::move(fileData->samples);

        SECTION("From Stereo File")
        {
            oalpp::SoundData const data = builder.fromFile("assets/test.mp3").create();

            REQUIRE(data.getNumberOfChannels() == 2);
            REQUIRE(data.getSampleRate() == 44100);

            auto const& samples_loaded = data.getSamples();
            REQUIRE(samples_loaded == samples_expected);
        }

        SECTION("With Gain Effect")
        {
            oalpp::effects::utility::Gain gain { 0.5f };
            oalpp::SoundData const data
                = builder.fromFile("assets/test.mp3").withEffect(gain).create();

            REQUIRE(data.getNumberOfChannels() == 2);
            REQUIRE(data.getSampleRate() == 44100);

            for (auto& s : samples_expected) {
                s *= 0.5f;
            }
            auto const& samples_loaded = data.getSamples();
            REQUIRE(samples_loaded == samples_expected);
        }

        SECTION("Left To Mono")
        {
            oalpp::SoundData const data
                = builder.fromFile("assets/test.mp3").onlyLeftChannel().create();

            REQUIRE(data.getNumberOfChannels() == 1);
            REQUIRE(data.getSampleRate() == 44100);

            std::vector<float> samples_expected_left;
            samples_expected_left.resize(samples_expected.size() / 2);

            for (auto index = 0U; index != samples_expected_left.size(); ++index) {
                samples_expected_left.at(index) = samples_expected.at(index * 2);
            }

            auto const& samples_loaded = data.getSamples();
            REQUIRE(samples_loaded.size() == samples_expected_left.size());
            REQUIRE(samples_loaded == samples_expected_left);
        }

        SECTION("Right To Mono")
        {
            oalpp::SoundData const data
                = builder.fromFile("assets/test.mp3").onlyRightChannel().create();

            REQUIRE(data.getNumberOfChannels() == 1);
            REQUIRE(data.getSampleRate() == 44100);

            std::vector<float> samples_expected_left;
            samples_expected_left.resize(samples_expected.size() / 2);

            for (auto index = 0U; index != samples_expected_left.size(); ++index) {
                samples_expected_left.at(index) = samples_expected.at(index * 2 + 1);
            }

            auto const& samples_loaded = data.getSamples();
            REQUIRE(samples_loaded.size() == samples_expected_left.size());
            REQUIRE(samples_loaded == samples_expected_left);
        }
    }
    SECTION("With Mono File")
    {
        nqr::NyquistIO loader;
        auto const fileData = std::make_unique<nqr::AudioData>();
        loader.Load(fileData.get(), "assets/test_mono.mp3");
        auto samples_expected = std::move(fileData->samples);

        SECTION("From Mono File")
        {
            oalpp::SoundData const data = builder.fromFile("assets/test_mono.mp3").create();

            REQUIRE(data.getNumberOfChannels() == 1);
            REQUIRE(data.getSampleRate() == 44100);

            auto const& samples_loaded = data.getSamples();
            REQUIRE(samples_loaded == samples_expected);
        }

        SECTION("With Gain Effect")
        {
            oalpp::effects::utility::Gain gain { 0.5f };
            oalpp::SoundData const data
                = builder.fromFile("assets/test_mono.mp3").withEffect(gain).create();

            REQUIRE(data.getNumberOfChannels() == 1);
            REQUIRE(data.getSampleRate() == 44100);

            for (auto& s : samples_expected) {
                s *= 0.5f;
            }
            auto const& samples_loaded = data.getSamples();
            REQUIRE(samples_loaded == samples_expected);
        }

        SECTION("Mono To Stereo")
        {
            oalpp::SoundData const data
                = builder.fromFile("assets/test_mono.mp3").toStereo().create();

            REQUIRE(data.getNumberOfChannels() == 2);
            REQUIRE(data.getSampleRate() == 44100);

            std::vector<float> samples_expected_stereo;
            samples_expected_stereo.resize(samples_expected.size() * 2);

            for (auto index = 0U; index != samples_expected.size(); ++index) {
                samples_expected_stereo.at(index * 2 + 0) = samples_expected.at(index);
                samples_expected_stereo.at(index * 2 + 1) = samples_expected.at(index);
            }

            auto const& samples_loaded = data.getSamples();
            REQUIRE(samples_loaded == samples_expected_stereo);
        }
    }
}
