#include "catch2/catch.hpp"
#include "sound_context.hpp"

TEST_CASE("Single context can be constructed", "[SoundContext]")
{
    REQUIRE_NOTHROW(SoundContext {});
}

TEST_CASE("Second context raises exception", "[SoundContext]")
{
    SoundContext ctx1 {};
    REQUIRE_THROWS(SoundContext {});
}
