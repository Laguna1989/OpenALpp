#include "ApprovalTests/ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "oalpp/effects/utility/convolution.hpp"
#include "oalpp/sound_data.hpp"

TEST_CASE("convolution")
{
    std::string const fileName { "assets/test1.ogg" };
    oalpp::SoundData buffer { fileName };
    oalpp::effects::utility::Convolution convolution { buffer.getSamples() };
    oalpp::SoundDataWithEffect soundWithEffect { buffer, convolution };

    ApprovalTests::Approvals::verifyAll(soundWithEffect.getSamples());
}
