#include "ApprovalTests/ApprovalTests.hpp"
#include <catch2/catch_test_macros.hpp>
#include <oalpp/effects/utility/phase_flip.hpp>
#include <oalpp/sound_data.hpp>

TEST_CASE("phase_flip")
{
    std::string const fileName { "assets/test1.wav" };
    oalpp::effects::utility::PhaseFlip phaseFlip {};

    oalpp::SoundDataBuilder builder;
    auto const soundWithEffect = builder.fromFile(fileName).withEffect(phaseFlip).create();

    ApprovalTests::Approvals::verifyAll(soundWithEffect.getSamples());
}
