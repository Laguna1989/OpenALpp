#include "ApprovalTests/ApprovalTests.hpp"
#include "approval_test_helpers.hpp"
#include "catch2/catch.hpp"
#include "oalpp/effects/utility/convolution.hpp"
#include "oalpp/sound_data.hpp"

TEST_CASE("convolution")
{
    std::string const fileName { "assets/test1.ogg" };
    oalpp::SoundData buffer { fileName };
    oalpp::effects::utility::Convolution convolution { buffer.getSamples() };
    oalpp::SoundDataWithEffect soundWithEffect { buffer, convolution };

    std::vector<int> values;
    values.resize(soundWithEffect.getSamples().size());

    std::transform(soundWithEffect.getSamples().cbegin(), soundWithEffect.getSamples().cend(),
        values.begin(), [](float const value) { return ApprovalTestHelpers::asInt(value, 100); });

    ApprovalTests::Approvals::verifyAll(values);
}
