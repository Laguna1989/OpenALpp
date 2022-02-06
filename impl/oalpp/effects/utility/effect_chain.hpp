#ifndef OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP
#define OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP

#include "oalpp/effects/mono_effect_interface.hpp"
#include <vector>

namespace oalpp {
namespace effects {
namespace utility {

class EffectChain : public oalpp::effects::MonoEffectInterface {
public:
    using EffectsT = std::vector<std::reference_wrapper<oalpp::effects::MonoEffectInterface>>;

    explicit EffectChain(
        std::vector<std::reference_wrapper<oalpp::effects::MonoEffectInterface>>& effects);
    float process(float input) override;
    void reset() override;

private:
    std::vector<std::reference_wrapper<oalpp::effects::MonoEffectInterface>> m_effects;
};

} // namespace utility
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP
