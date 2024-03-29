#include "sound_data_fake.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <oalpp/sound/sound.hpp>
#include <oalpp/sound_context/sound_context.hpp>
#include <cmath>

using namespace oalpp;

TEST_CASE("Sound is not default constructible", "[Sound]")
{
    static_assert(
        !std::is_default_constructible<Sound>::value, "Sound is not default constructible");
}

TEST_CASE("Sound is not playing by default", "[Sound]")
{
    SoundContext const ctx;
    SoundDataMonoFake const buffer;
    Sound snd { buffer };

    REQUIRE_FALSE(snd.isPlaying());
}

TEST_CASE("Sound volume test", "[Sound]")
{
    SoundContext const ctx;
    SoundDataMonoFake const buffer;
    Sound snd { buffer };

    SECTION("default volume value") { REQUIRE(1.0f == snd.getVolume()); }
    SECTION("volume after setVolume")
    {
        float const newVolume = GENERATE(0.5f, 1.0f, 0.1f, 0.0f);
        snd.setVolume(newVolume);
        REQUIRE(newVolume == snd.getVolume());
    }

    SECTION("invalid setVolume value")
    {
        float const newVolume = GENERATE(-1.5f, -0.1f, 1.1f, 9001.0f, -666.0f);
        REQUIRE_THROWS(snd.setVolume(newVolume));
    }
}

TEST_CASE("Sound position and pan test", "[Sound]")
{
    SoundContext const ctx;
    SoundDataMonoFake const buffer;
    Sound snd { buffer };

    SECTION("default position value")
    {
        auto const pos = snd.getPosition();
        REQUIRE(Position { 0.0f, 0.0f, -1.0f } == pos);
    }

    SECTION("position after setPosition")
    {
        auto const newPosition = GENERATE(Position { 0.0f, 0.0f, 0.0f },
            Position { 1.0f, 0.0f, 0.0f }, Position { 0.0f, 1.0f, 0.0f },
            Position { 0.0f, 0.0f, 1.0f }, Position { -100.0f, 0.0f, 0.0f },
            Position { 0.0f, -100.0f, 0.0f }, Position { 0.0f, 0.0f, -100.0f },
            Position { 5.0f, 7.0f, 8.0f }, Position { -10.0f, -17.0f, -2.0f });

        snd.setPosition(newPosition);
        REQUIRE(newPosition == snd.getPosition());
    }

    SECTION("position after setPan")
    {
        auto const conversion = [](float pan) {
            return Position { pan, 0, -static_cast<float>(std::sqrt(1.0f - pan * pan)) };
        };
        float const newPan = GENERATE(0.5f, 1.0f, 0.1f, 0.0f);
        auto const expectedPosition = conversion(newPan);
        snd.setPan(newPan);
        REQUIRE(expectedPosition == snd.getPosition());
    }

    SECTION("invalid pan value")
    {
        float const newPan = GENERATE(-1.5f, -1.1f, 1.1f, 1.5f, 9001.0f, -666.0f);
        REQUIRE_THROWS(snd.setPan(newPan));
    }
}

TEST_CASE("Sound pitch test", "[Sound]")
{
    SoundContext const ctx;
    SoundDataMonoFake const buffer;
    Sound snd { buffer };

    SECTION("default pitch value") { REQUIRE(1.0f == snd.getPitch()); }
    SECTION("pitch after setPitch")
    {
        float const newPitch = GENERATE(0.1f, 0.5f, 1.0f, 100.0f);
        snd.setPitch(newPitch);
        REQUIRE(newPitch == snd.getPitch());
    }

    SECTION("invalid pitch value")
    {
        float const newPitch = GENERATE(-0.1f, -100.0f);
        REQUIRE_THROWS(snd.setPitch(newPitch));
    }
}

TEST_CASE("Sound looping test", "[Sound]")
{
    SoundContext const ctx;
    SoundDataMonoFake const buffer;
    Sound snd { buffer };

    SECTION("default looping value") { REQUIRE(false == snd.getIsLooping()); }
    SECTION("looping after setIsLooping")
    {
        snd.setIsLooping(true);
        REQUIRE(true == snd.getIsLooping());
    }

    SECTION("not looping after unset looping")
    {
        snd.setIsLooping(true);
        snd.setIsLooping(false);
        REQUIRE(false == snd.getIsLooping());
    }
}

TEST_CASE("Sound pan stereo sound test", "[Sound]")
{
    SoundContext const ctx;
    SoundDataStereoFake const buffer;
    Sound snd { buffer };

    SECTION("default position value")
    {
        auto const pos = snd.getPosition();
        REQUIRE(Position { 0.0f, 0.0f, -1.0f } == pos);
    }
    SECTION("pan stereo sound always raises exception")
    {
        float const newPan
            = GENERATE(-1.5f, -1.1f, 1.1f, 1.5f, 9001.0f, -666.0f, 0.5f, 1.0f, 0.1f, 0.0f);
        REQUIRE_THROWS(snd.setPan(newPan));
    }
}

TEST_CASE("is playing is true after play ", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    fake.m_samples.resize(44100);
    Sound snd { fake };
    snd.play();
    REQUIRE(true == snd.isPlaying());
}

TEST_CASE("is playing is false after stop", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    fake.m_samples.resize(44100);
    Sound snd { fake };
    snd.play();
    snd.stop();
    REQUIRE(false == snd.isPlaying());
}

TEST_CASE("is playing is false after pause", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    fake.m_samples.resize(44100);
    Sound snd { fake };
    snd.play();
    snd.pause();
    REQUIRE(false == snd.isPlaying());
}

TEST_CASE("stop twice does not raise exception", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    fake.m_samples.resize(44100);
    Sound snd { fake };
    snd.play();
    snd.stop();
    REQUIRE_NOTHROW(snd.stop());
}

TEST_CASE("is playing is true for play after stop", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    fake.m_samples.resize(44100);
    Sound snd { fake };
    snd.play();
    snd.stop();
    snd.play();
    REQUIRE(true == snd.isPlaying());
}

TEST_CASE("Sound getLength", "[Sound]")
{
    SoundContext ctx;

    SECTION("Empty SoundDataMonoFake results in length zero")
    {
        SoundDataMonoFake fake;
        Sound snd { fake };
        REQUIRE(0 == snd.getLengthInSamples());
        REQUIRE(0.0f == snd.getLengthInSeconds());
    }

    SECTION("Filled SoundDataMonoFake results in correct length in samples")
    {
        SoundDataMonoFake fake;
        std::size_t const newSampleCount = GENERATE(1u, 10u, 100u, 1000u);
        fake.m_samples.resize(newSampleCount);
        Sound snd { fake };
        REQUIRE(newSampleCount == snd.getLengthInSamples());
    }

    SECTION("Filled SoundDataMonoFake results in correct length in seconds")
    {
        SoundDataMonoFake fake;
        std::size_t const newSampleCount = fake.getSampleRate();
        fake.m_samples.resize(newSampleCount);
        Sound snd { fake };
        REQUIRE(1.0f == snd.getLengthInSeconds());
    }

    SECTION("Filled SoundDataMonoFake results in correct length")
    {
        SoundDataMonoFake fake;
        std::size_t const newSampleCount = GENERATE(1u, 10u, 100u, 1000u);
        fake.m_samples.resize(newSampleCount);
        Sound snd { fake };
        REQUIRE(newSampleCount == snd.getLengthInSamples());
    }

    SECTION("Empty SoundDataStereoFake results in length zero")
    {
        SoundDataStereoFake fake;
        Sound snd { fake };
        REQUIRE(0 == snd.getLengthInSamples());
        REQUIRE(0.0f == snd.getLengthInSeconds());
    }

    SECTION("Filled SoundDataStereoFake results in correct length")
    {
        SoundDataStereoFake fake;
        std::size_t const newSampleCount = GENERATE(2u, 20u, 200u, 2000u);
        fake.m_samples.resize(newSampleCount);
        Sound snd { fake };
        REQUIRE(newSampleCount / 2u == snd.getLengthInSamples());
    }

    SECTION("Filled SoundDataStereoFake results in correct length in seconds")
    {
        SoundDataStereoFake fake;
        std::size_t const newSampleCount = fake.getSampleRate();
        fake.m_samples.resize(2 * newSampleCount);
        Sound snd { fake };
        REQUIRE(1.0f == snd.getLengthInSeconds());
    }
}

TEST_CASE("Sound update test", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    SECTION("update with non-looping sound (varying sizes) does not raise an exception")
    {
        auto const sampleSizeFactorInBufferSizes
            = GENERATE(0.2f, 1.0f, 1.5f, 2.0f, 3.5f, 4.0f, 4.5f);
        fake.m_samples.resize(Sound::BUFFER_SIZE * sampleSizeFactorInBufferSizes);
        Sound snd { fake };
        snd.play();
        auto const start = std::chrono::system_clock::now();
        while (true) {
            REQUIRE_NOTHROW(snd.update());

            auto const now = std::chrono::system_clock::now();
            float const elapsedSeconds
                = std::chrono::duration_cast<std::chrono::microseconds>(now - start).count()
                / 1000.0f / 1000.0f;

            // break test after 6 s or when sound stops playing
            if (elapsedSeconds >= 6.0f || !snd.isPlaying()) {
                snd.pause();
                break;
            }
        }
    }
    SECTION("update with looping sound (varying sizes) does not stop playing")
    {
        auto const sampleSizeFactorInBufferSizes
            = GENERATE(0.2f, 1.0f, 1.5f, 2.0f, 3.5f, 4.0f, 4.5f);
        fake.m_samples.resize(Sound::BUFFER_SIZE * sampleSizeFactorInBufferSizes);
        Sound snd { fake };
        snd.setIsLooping(true);
        snd.play();
        auto const start = std::chrono::system_clock::now();
        while (true) {
            snd.update();
            REQUIRE(snd.isPlaying());

            auto const now = std::chrono::system_clock::now();
            float const elapsedSeconds
                = std::chrono::duration_cast<std::chrono::microseconds>(now - start).count()
                / 1000.0f / 1000.0f;

            // break test after 7 s
            if (elapsedSeconds >= 7.0f) {
                snd.pause();
                break;
            }
        }
    }
}

TEST_CASE("Sound getCurrentPosition", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    SECTION("Empty SoundDataMonoFake results in correct initial Position in seconds")
    {
        Sound snd { fake };
        REQUIRE(0.0f == snd.getCurrentOffsetInSeconds());
    }

    SECTION("Empty SoundDataMonoFake results in correct initial Position in samples")
    {
        Sound snd { fake };
        REQUIRE(0 == snd.getCurrentOffsetInSamples());
    }

    SECTION("after complete sample is played, getCurrentPosition should return 0.0f seconds")
    {
        // this one test uses a longer sound source to test all branches in update
        fake.m_samples.resize(Sound::BUFFER_SIZE * Sound::BUFFER_COUNT + 100);
        Sound snd { fake };
        snd.play();
        while (snd.isPlaying()) {
            snd.update();
        }
        REQUIRE(0.0f == snd.getCurrentOffsetInSeconds());
    }

    SECTION("after complete sample is played, getCurrentPosition should return 0 samples")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake };
        snd.play();
        while (snd.isPlaying()) {
            snd.update();
        }
        REQUIRE(0u == snd.getCurrentOffsetInSamples());
    }

    SECTION("getCurrentPositionSeconds is increasing while playing")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake };
        snd.play();
        float oldValue = 0.0f;
        while (snd.isPlaying()) {
            snd.update();
            auto const newValue = snd.getCurrentOffsetInSeconds();
            if (newValue != 0.0f) {
                REQUIRE(newValue >= oldValue);
                oldValue = newValue;
            }
        }
    }

    SECTION("getCurrentPositionSamples is increasing while playing")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake };
        snd.play();
        std::size_t oldValue = 0u;
        while (snd.isPlaying()) {
            snd.update();
            auto const newValue = snd.getCurrentOffsetInSamples();
            if (newValue != 0u) {
                REQUIRE(newValue >= oldValue);
                oldValue = newValue;
            }
        }
    }

    SECTION("getCurrentPositionSamples is reset on stop")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake };
        snd.play();
        while (snd.isPlaying()) {
            snd.update();
            auto const newValue = snd.getCurrentOffsetInSamples();
            if (newValue != 0u) {
                snd.stop();
                REQUIRE(0.0f == snd.getCurrentOffsetInSamples());
                break;
            }
        }
    }

    SECTION("getCurrentPositionSeconds is reset on stop")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake };
        snd.play();
        while (snd.isPlaying()) {
            snd.update();
            auto const newValue = snd.getCurrentOffsetInSeconds();
            if (newValue != 0.0f) {
                snd.stop();
                REQUIRE(0.0f == snd.getCurrentOffsetInSeconds());
                break;
            }
        }
    }

    SECTION("getCurrentPositionSamples is not reset on pause")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake };
        snd.play();
        while (snd.isPlaying()) {
            snd.update();
            auto const newValue = snd.getCurrentOffsetInSamples();
            if (newValue != 0u) {
                snd.pause();
                REQUIRE(0u != snd.getCurrentOffsetInSamples());
                break;
            }
        }
    }

    SECTION("getCurrentPositionSeconds is reset on pause")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake };
        snd.play();
        while (snd.isPlaying()) {
            snd.update();
            auto const newValue = snd.getCurrentOffsetInSeconds();
            if (newValue != 0.0f) {
                snd.pause();
                REQUIRE(0.0f != snd.getCurrentOffsetInSeconds());
                break;
            }
        }
    }
}

TEST_CASE("Sound Constructor without SoundContext raises exception", "[Sound]")
{
    SoundDataMonoFake fake;
    REQUIRE_THROWS(Sound { fake });
}

TEST_CASE("Sound actions without context raises exception", "[Sound]")
{
    std::unique_ptr<SoundContext> ctx = std::make_unique<SoundContext>();
    SoundDataMonoFake fake;
    Sound snd { fake };

    // note: openAL errors about buffers and sound not deleted are expected and intentional for this
    // test. The error messages are triggered by deleting the SoundContext which is a mandatory step
    // for this test.
    ctx.reset();
    SECTION("play") { REQUIRE_THROWS(snd.play()); }
    SECTION("stop") { REQUIRE_THROWS(snd.stop()); }
    SECTION("pause") { REQUIRE_THROWS(snd.pause()); }
}
