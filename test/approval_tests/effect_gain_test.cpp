#include "ApprovalTests/ApprovalTests.hpp"
#include <catch2/catch_test_macros.hpp>
#include <oalpp/effects/utility/gain.hpp>
#include <oalpp/sound_data.hpp>

TEST_CASE("gain")
{
    std::string const fileName { "assets/test1.wav" };
    oalpp::SoundDataBuilder builder;
    SECTION("1.0")
    {
        oalpp::effects::utility::Gain gain { 1.0f };
        auto const soundWithEffect = builder.fromFile("assets/test1.wav").withEffect(gain).create();

        ApprovalTests::Approvals::verifyAll(soundWithEffect.getSamples());
    }
    SECTION("2.0")
    {
        oalpp::effects::utility::Gain gain { 2.0f };
        auto const soundWithEffect = builder.fromFile("assets/test1.wav").withEffect(gain).create();

        ApprovalTests::Approvals::verifyAll(soundWithEffect.getSamples());
    }
}
