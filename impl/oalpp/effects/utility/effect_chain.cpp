#include "effect_chain.hpp"

namespace oalpp {
namespace effects {
namespace utility {

EffectChain::EffectChain(
    std::vector<std::reference_wrapper<oalpp::effects::MonoEffectIterative>>& effects)
    : m_effects { effects }
{
}

float EffectChain::process(float input)
{
    auto result = input;
    for (auto effect : m_effects) {
        result = effect.get().process(result);
    }
    return result;
}

void EffectChain::reset()
{
    for (auto effect : m_effects) {
        effect.get().reset();
    }
}

} // namespace utility
} // namespace effects
} // namespace oalpp
