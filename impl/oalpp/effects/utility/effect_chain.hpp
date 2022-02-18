#ifndef OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP
#define OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP

#include "oalpp/effects/mono_effect_bulk.hpp"
#include <functional>
#include <vector>

namespace oalpp {
namespace effects {
namespace utility {

class EffectChain : public oalpp::effects::MonoEffectBulk {
public:
    using EffectsT = std::vector<std::reference_wrapper<oalpp::effects::MonoEffectBulk>>;

    explicit EffectChain(
        std::vector<std::reference_wrapper<oalpp::effects::MonoEffectBulk>>& effects);
    std::vector<float> process(std::vector<float> const& input) override;

private:
    std::vector<std::reference_wrapper<oalpp::effects::MonoEffectBulk>> m_effects;
};

} // namespace utility
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_UTILITY_EFFECT_CHAIN_HPP
