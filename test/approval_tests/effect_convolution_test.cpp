#include "ApprovalTests/ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "oalpp/effects/utility/convolution.hpp"
#include "oalpp/sound_data.hpp"
#include "approval_test_helpers.hpp"

TEST_CASE("convolution")
{
    std::string const fileName { "assets/test1.wav" };
    oalpp::SoundData buffer { fileName };
    oalpp::effects::utility::Convolution convolution { buffer.getSamples() };
    oalpp::SoundDataWithEffect soundWithEffect { buffer, convolution };

    // note: Due to platform dependent float behavior, the result needs to be converted to int for
    // the approval tests to work.
    ApprovalTests::Approvals::verifyAll(ApprovalTestHelpers::asInt(soundWithEffect.getSamples(), 100));
}
