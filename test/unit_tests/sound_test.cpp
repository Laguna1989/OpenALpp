#include "catch2/catch.hpp"
#include "sound.hpp"
#include "sound_context.hpp"

TEST_CASE("Sound is not default constructible", "[Sound]")
{
    static_assert(!std::is_default_constructible_v<Sound>, "Sound is not default constructible");
}

class SoundDataMonoFake : public SoundDataInterface {
public:
    int getNumberOfChannels() const override { return 1; }
    int getSampleRate() const override { return 44100; }
    std::vector<short> const& getSamples() const override { return m_emptySamples; }
    std::vector<short> m_emptySamples {};
};

class SoundDataStereoFake : public SoundDataInterface {
public:
    int getNumberOfChannels() const override { return 2; }
    int getSampleRate() const override { return 44100; }
    std::vector<short> const& getSamples() const override { return m_emptySamples; }
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

TEST_CASE("Sound pan test", "[Sound]")
{
    SoundContext const ctx;
    SoundDataMonoFake const buffer;
    Sound snd { buffer, ctx };

    SECTION("default pan value") { REQUIRE(0.0f == snd.getPan()); }
    SECTION("pan after setPan")
    {
        float const newPan = GENERATE(0.5f, 1.0f, 0.1f, 0.0f);
        snd.setPan(newPan);
        REQUIRE(newPan == snd.getPan());
    }

    SECTION("invalid pan value")
    {
        float const newPan = GENERATE(-1.5f, -1.1f, 1.1f, 1.5f, 9001.0f, -666.0f);
        REQUIRE_THROWS(snd.setPan(newPan));
    }
}

TEST_CASE("Sound pan stereo sound test", "[Sound]")
{
    SoundContext const ctx;
    SoundDataStereoFake const buffer;
    Sound snd { buffer, ctx };

    SECTION("default pan value") { REQUIRE(0.0f == snd.getPan()); }
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
