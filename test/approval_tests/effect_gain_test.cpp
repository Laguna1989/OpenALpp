#include "ApprovalTests/ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "oalpp/effects/utility/gain.hpp"
#include "oalpp/sound_data.hpp"

TEST_CASE("gain")
{
    SECTION("1.0")
    {
        std::string const fileName { "assets/test1.ogg" };
        oalpp::effects::utility::Gain gain { 1.0f };
        oalpp::SoundData buffer { fileName };
        oalpp::SoundDataWithEffect soundWithEffect { buffer, gain };

        ApprovalTests::Approvals::verifyAll(soundWithEffect.getSamples());
    }
    SECTION("2.0")
    {
        std::string const fileName { "assets/test1.ogg" };
        oalpp::effects::utility::Gain gain { 2.0f };
        oalpp::SoundData buffer { fileName };
        oalpp::SoundDataWithEffect soundWithEffect { buffer, gain };

        ApprovalTests::Approvals::verifyAll(soundWithEffect.getSamples());
    }
}
