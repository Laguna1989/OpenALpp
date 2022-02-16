#include "catch2/catch.hpp"
#include "oalpp/sound_context/sound_context.hpp"

using namespace oalpp;

TEST_CASE("Single context is default constructible", "[SoundContext]")
{
    static_assert(std::is_default_constructible<SoundContext>::value,
        "Sound context not default constructible");
}

TEST_CASE("Single context can be constructed", "[SoundContext]")
{
    auto func = []() { SoundContext ctx {}; };
    REQUIRE_NOTHROW(func());
}

TEST_CASE("Second context raises exception", "[SoundContext]")
{
    SoundContext ctx1 {};
    REQUIRE_THROWS(SoundContext {});
}
