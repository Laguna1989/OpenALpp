#ifndef OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP
#define OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP

#include "oalpp/effects/mono_effect_iterative.hpp"
#include <functional>
#include <vector>

namespace oalpp {
namespace effects {
namespace utility {

class EffectChain : public oalpp::effects::MonoEffectIterative {
public:
    using EffectsT = std::vector<std::reference_wrapper<oalpp::effects::MonoEffectIterative>>;

    explicit EffectChain(
        std::vector<std::reference_wrapper<oalpp::effects::MonoEffectIterative>>& effects);
    float process(float input) override;
    void reset() override;

private:
    std::vector<std::reference_wrapper<oalpp::effects::MonoEffectIterative>> m_effects;
};

} // namespace utility
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP
