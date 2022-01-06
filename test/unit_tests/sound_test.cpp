#include "catch2/catch.hpp"
#include "sound.hpp"
#include "sound_context.hpp"

TEST_CASE("Sound is not default constructible", "[Sound]")
{
    static_assert(!std::is_default_constructible_v<Sound>, "Sound is not default constructible");
}

class SoundDataFake : public SoundDataInterface {
public:
    int getNumberOfChannels() const override { return 1; }
    int getSampleRate() const override { return 44100; }
    std::vector<short> const& getSamples() const override { return m_emptySamples; }
    std::vector<short> m_emptySamples {};
};

TEST_CASE("Sound is not playing by default", "[Sound]")
{
    SoundContext ctx;
    SoundDataFake buffer;
    Sound snd { buffer, ctx };

    SECTION("default is Playing") { REQUIRE_FALSE(snd.isPlaying()); }
    SECTION("default volume") { REQUIRE(1.0f == snd.getVolume()); }
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

TEST_CASE("Sound volume test", "[Sound]")
{
    SoundContext ctx;
    SoundDataFake buffer;
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

TEST_CASE("Sound play does not raise exception", "[Sound]")
{
    SoundContext ctx;
    SoundDataFake fake;
    Sound snd { fake, ctx };
    REQUIRE_NOTHROW(snd.play());
}
