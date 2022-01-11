#include "catch2/catch.hpp"
#include "sound_context.hpp"

using namespace oalpp;

TEST_CASE("Single context is default constructible", "[SoundContext]")
{
    static_assert(
        std::is_default_constructible_v<SoundContext>, "Sound context not default constructible");
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
