#ifndef OPENALPP_EFFECTS_UTILITY_PHASE_FLIP_HPP
#define OPENALPP_EFFECTS_UTILITY_PHASE_FLIP_HPP

#include "oalpp/effects/mono_effect_bulk.hpp"

namespace oalpp {
namespace effects {
namespace utility {
class PhaseFlip : public oalpp::effects::MonoEffectBulk {
public:
    std::vector<float> process(std::vector<float> const& input) override;
};
} // namespace utility
} // namespace effects
} // namespace oalpp

#endif
