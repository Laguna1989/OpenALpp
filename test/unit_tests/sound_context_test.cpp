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

TEST_CASE("Create Context which cannot allocate device throws", "[SoundContext]")
{
    std::function<std::unique_ptr<ALCdevice, SoundContext::DeviceDestroyer>()> factory = []() {
        return std::unique_ptr<ALCdevice, SoundContext::DeviceDestroyer>(
            nullptr, SoundContext::DeviceDestroyer());
    };
    REQUIRE_THROWS(SoundContext { factory });
}
