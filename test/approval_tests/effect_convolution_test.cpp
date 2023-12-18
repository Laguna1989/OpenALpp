#include "ApprovalTests/ApprovalTests.hpp"
#include "approval_test_helpers.hpp"
#include <catch2/catch.hpp>
#include <oalpp/effects/utility/convolution.hpp>
#include <oalpp/sound_data.hpp>

TEST_CASE("convolution")
{
    std::string const fileName { "assets/test1.wav" };
    oalpp::effects::utility::Convolution convolution {
        oalpp::SoundDataBuilder().fromFile(fileName).create().getSamples()
    };

    auto const soundWithEffect
        = oalpp::SoundDataBuilder().fromFile("assets/test1.wav").withEffect(convolution).create();

    // note: Due to platform dependent float behavior, the result needs to be converted to int for
    // the approval tests to work.
    ApprovalTests::Approvals::verifyAll(
        ApprovalTestHelpers::asInt(soundWithEffect.getSamples(), 100));
}
