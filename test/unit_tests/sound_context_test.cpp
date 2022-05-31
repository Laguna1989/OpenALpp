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

TEST_CASE("Create SoundContext which cannot allocate ALDevice throws", "[SoundContext]")
{
    SoundContext::DeviceFactoryT factory = []() {
        return std::unique_ptr<ALCdevice, SoundContext::DeviceDestroyer>(
            nullptr, SoundContext::DeviceDestroyer());
    };
    REQUIRE_THROWS(SoundContext { factory });
}

TEST_CASE("First SoundContext fails, second SoundContext can be created", "[SoundContext]")
{
    SoundContext::DeviceFactoryT factory = []() {
        return std::unique_ptr<ALCdevice, SoundContext::DeviceDestroyer>(
            nullptr, SoundContext::DeviceDestroyer());
    };
    REQUIRE_THROWS(SoundContext { factory });

    // second context can in fact be created after first context creation failed
    SoundContext ctx1 {};
}

TEST_CASE("Create SoundContext which cannot allocate ALContext throws", "[SoundContext]")
{
    SoundContext::ContextFactoryT factory = [](ALCdevice* /* unused */) {
        return std::unique_ptr<ALCcontext, SoundContext::ContextDestroyer>(
            nullptr, SoundContext::ContextDestroyer());
    };
    REQUIRE_THROWS(SoundContext { nullptr, factory });
}
