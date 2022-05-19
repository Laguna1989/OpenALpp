#include "ApprovalTests/ApprovalTests.hpp"
#include "catch2/catch.hpp"
#include "oalpp/effects/utility/phase_flip.hpp"
#include "oalpp/sound_data.hpp"

TEST_CASE("phase_flip")
{
    std::string const fileName { "assets/test1.wav" };
    oalpp::SoundData buffer { fileName };
    oalpp::effects::utility::PhaseFlip phaseFlip { };
    oalpp::SoundDataWithEffect soundWithEffect { buffer, phaseFlip };

    ApprovalTests::Approvals::verifyAll(soundWithEffect.getSamples());
}
