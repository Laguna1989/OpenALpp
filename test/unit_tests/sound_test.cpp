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
    REQUIRE_FALSE(snd.isPlaying());
}

TEST_CASE("Sound play does not raise exception", "[Sound]")
{
    SoundContext ctx;
    SoundDataFake fake;
    Sound snd { fake, ctx };
    REQUIRE_NOTHROW(snd.play());
}
