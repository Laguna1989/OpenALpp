#include "catch2/catch.hpp"
#include "oalpp/sound.hpp"
#include "oalpp/sound_context.hpp"

using namespace oalpp;

TEST_CASE("Sound is not default constructible", "[Sound]")
{
    static_assert(
        !std::is_default_constructible<Sound>::value, "Sound is not default constructible");
}

class SoundDataMonoFake : public SoundDataInterface {
public:
    int getNumberOfChannels() const override { return 1; }
    int getSampleRate() const override { return 44100; }
    std::vector<float> const& getSamples() const override { return m_samples; }
    std::vector<float> m_samples {};
};

class SoundDataStereoFake : public SoundDataInterface {
public:
    int getNumberOfChannels() const override { return 2; }
    int getSampleRate() const override { return 44100; }
    std::vector<float> const& getSamples() const override { return m_samples; }
    std::vector<float> m_samples {};
};

TEST_CASE("Sound is not playing by default", "[Sound]")
{
    SoundContext const ctx;
    SoundDataMonoFake const buffer;
    Sound snd { buffer, ctx };

    REQUIRE_FALSE(snd.isPlaying());
}

TEST_CASE("Sound volume test", "[Sound]")
{
    SoundContext const ctx;
    SoundDataMonoFake const buffer;
    Sound snd { buffer, ctx };

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
    Sound snd { buffer, ctx };

    SECTION("default position value")
    {
        auto const pos = snd.getPosition();
        REQUIRE(std::array<float, 3> { 0.0f, 0.0f, -1.0f } == pos);
    }

    SECTION("position after setPosition")
    {
        auto const newPosition = GENERATE(std::array<float, 3> { 0.0f, 0.0f, 0.0f },
            std::array<float, 3> { 1.0f, 0.0f, 0.0f }, std::array<float, 3> { 0.0f, 1.0f, 0.0f },
            std::array<float, 3> { 0.0f, 0.0f, 1.0f }, std::array<float, 3> { -100.0f, 0.0f, 0.0f },
            std::array<float, 3> { 0.0f, -100.0f, 0.0f },
            std::array<float, 3> { 0.0f, 0.0f, -100.0f }, std::array<float, 3> { 5.0f, 7.0f, 8.0f },
            std::array<float, 3> { -10.0f, -17.0f, -2.0f });

        snd.setPosition(newPosition);
        REQUIRE(newPosition == snd.getPosition());
    }

    SECTION("position after setPan")
    {
        auto const conversion = [](float pan) {
            return std::array<float, 3> { pan, 0, -static_cast<float>(sqrt(1.0f - pan * pan)) };
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
    Sound snd { buffer, ctx };

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
    Sound snd { buffer, ctx };

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
    Sound snd { buffer, ctx };

    SECTION("default position value")
    {
        auto const pos = snd.getPosition();
        REQUIRE(std::array<float, 3> { 0.0f, 0.0f, -1.0f } == pos);
    }
    SECTION("pan stereo sound always raises exception")
    {
        float const newPan
            = GENERATE(-1.5f, -1.1f, 1.1f, 1.5f, 9001.0f, -666.0f, 0.5f, 1.0f, 0.1f, 0.0f);
        REQUIRE_THROWS(snd.setPan(newPan));
    }
}

TEST_CASE("Play does not raise exception", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    Sound snd { fake, ctx };
    REQUIRE_NOTHROW(snd.play());
}

TEST_CASE("Sound getLength", "[Sound]")
{
    SoundContext ctx;

    SECTION("Empty SoundDataMonoFake results in length zero")
    {
        SoundDataMonoFake fake;
        Sound snd { fake, ctx };
        REQUIRE(0 == snd.getLengthInSamples());
        REQUIRE(0.0f == snd.getLengthInSeconds());
    }

    SECTION("Filled SoundDataMonoFake results in correct length in samples")
    {
        SoundDataMonoFake fake;
        std::size_t const newSampleCount = GENERATE(1u, 10u, 100u, 1000u);
        fake.m_samples.resize(newSampleCount);
        Sound snd { fake, ctx };
        REQUIRE(newSampleCount == snd.getLengthInSamples());
    }

    SECTION("Filled SoundDataMonoFake results in correct length in seconds")
    {
        SoundDataMonoFake fake;
        std::size_t const newSampleCount = fake.getSampleRate();
        fake.m_samples.resize(newSampleCount);
        Sound snd { fake, ctx };
        REQUIRE(1.0f == snd.getLengthInSeconds());
    }

    SECTION("Filled SoundDataMonoFake results in correct length")
    {
        SoundDataMonoFake fake;
        std::size_t const newSampleCount = GENERATE(1u, 10u, 100u, 1000u);
        fake.m_samples.resize(newSampleCount);
        Sound snd { fake, ctx };
        REQUIRE(newSampleCount == snd.getLengthInSamples());
    }

    SECTION("Empty SoundDataStereoFake results in length zero")
    {
        SoundDataStereoFake fake;
        Sound snd { fake, ctx };
        REQUIRE(0 == snd.getLengthInSamples());
        REQUIRE(0.0f == snd.getLengthInSeconds());
    }

    SECTION("Filled SoundDataStereoFake results in correct length")
    {
        SoundDataStereoFake fake;
        std::size_t const newSampleCount = GENERATE(2u, 20u, 200u, 2000u);
        fake.m_samples.resize(newSampleCount);
        Sound snd { fake, ctx };
        REQUIRE(newSampleCount / 2u == snd.getLengthInSamples());
    }

    SECTION("Filled SoundDataStereoFake results in correct length in seconds")
    {
        SoundDataStereoFake fake;
        std::size_t const newSampleCount = fake.getSampleRate();
        fake.m_samples.resize(2 * newSampleCount);
        Sound snd { fake, ctx };
        REQUIRE(1.0f == snd.getLengthInSeconds());
    }
}

TEST_CASE("Sound getCurrentPosition", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    SECTION("Empty SoundDataMonoFake results in correct initial Position in seconds")
    {
        Sound snd { fake, ctx };
        REQUIRE(0.0f == snd.getCurrentPositionInSeconds());
    }

    SECTION("Empty SoundDataMonoFake results in correct initial Position in samples")
    {
        Sound snd { fake, ctx };
        REQUIRE(0 == snd.getCurrentPositionInSamples());
    }

    SECTION("after complete sample is played, getCurrentPosition should return 0.0f seconds")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake, ctx };
        snd.play();
        while (snd.isPlaying()) {
            snd.update();
        }
        REQUIRE(0.0f == snd.getCurrentPositionInSeconds());
    }

    SECTION("after complete sample is played, getCurrentPosition should return 0 samples")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake, ctx };
        snd.play();
        while (snd.isPlaying()) {
            snd.update();
        }
        REQUIRE(0u == snd.getCurrentPositionInSamples());
    }

    SECTION("getCurrentPositionSeconds is increasing while playing")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake, ctx };
        snd.play();
        float oldValue = 0.0f;
        while (snd.isPlaying()) {
            snd.update();
            float const newValue = snd.getCurrentPositionInSeconds();
            if (newValue != 0.0f) {
                REQUIRE(newValue >= oldValue);
                oldValue = newValue;
            }
        }
    }

    SECTION("getCurrentPositionSamples is increasing while playing")
    {
        fake.m_samples.resize(8820);
        Sound snd { fake, ctx };
        snd.play();
        std::size_t oldValue = 0u;
        while (snd.isPlaying()) {
            snd.update();
            std::size_t const newValue = snd.getCurrentPositionInSamples();
            if (newValue != 0u) {
                REQUIRE(newValue >= oldValue);
                oldValue = newValue;
            }
        }
    }
}
