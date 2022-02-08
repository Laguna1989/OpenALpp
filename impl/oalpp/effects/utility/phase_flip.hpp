#ifndef OPENALPP_EFFECTS_UTILITY_PHASE_FLIP_HPP
#define OPENALPP_EFFECTS_UTILITY_PHASE_FLIP_HPP

#include "oalpp/effects/mono_effect_interface.hpp"

namespace oalpp {
namespace effects {
namespace utility {
class PhaseFlip : public oalpp::effects::MonoEffectInterface {
public:
    float process(float input) override;
    void reset() override;
};
} // namespace utility
} // namespace effects
} // namespace oalpp

#endif