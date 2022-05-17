#include "ApprovalTests/ApprovalTests.hpp"
#include "approval_test_helpers.hpp"
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

        std::vector<int> values;
        values.resize(soundWithEffect.getSamples().size());

        std::transform(soundWithEffect.getSamples().cbegin(), soundWithEffect.getSamples().cend(),
            values.begin(),
            [](float const value) { return ApprovalTestHelpers::asInt(value, 1000); });

        ApprovalTests::Approvals::verifyAll(values);
    }
    SECTION("2.0")
    {
        std::string const fileName { "assets/test1.ogg" };
        oalpp::effects::utility::Gain gain { 2.0f };
        oalpp::SoundData buffer { fileName };
        oalpp::SoundDataWithEffect soundWithEffect { buffer, gain };

        std::vector<int> values;
        values.resize(soundWithEffect.getSamples().size());

        std::transform(soundWithEffect.getSamples().cbegin(), soundWithEffect.getSamples().cend(),
            values.begin(),
            [](float const value) { return ApprovalTestHelpers::asInt(value, 100); });

        ApprovalTests::Approvals::verifyAll(values);
    }
}
