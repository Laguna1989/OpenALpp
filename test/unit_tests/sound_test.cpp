#include "catch2/catch.hpp"
#include "sound.hpp"
#include "sound_context.hpp"

using namespace oalpp;

TEST_CASE("Sound is not default constructible", "[Sound]")
{
    static_assert(!std::is_default_constructible_v<Sound>, "Sound is not default constructible");
}

class SoundDataMonoFake : public SoundDataInterface {
public:
    int getNumberOfChannels() const override { return 1; }
    int getSampleRate() const override { return 44100; }
    std::vector<char> const& getSamples() const override { return m_emptySamples; }
    std::vector<short> m_emptySamples {};
};

class SoundDataStereoFake : public SoundDataInterface {
public:
    int getNumberOfChannels() const override { return 2; }
    int getSampleRate() const override { return 44100; }
    std::vector<char> const& getSamples() const override { return m_emptySamples; }
    std::vector<short> m_emptySamples {};
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
            return std::array<float, 3> { pan, 0, -sqrt(1.0f - pan * pan) };
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

TEST_CASE("Sound play does not raise exception", "[Sound]")
{
    SoundContext ctx;
    SoundDataMonoFake fake;
    Sound snd { fake, ctx };
    REQUIRE_NOTHROW(snd.play());
}
