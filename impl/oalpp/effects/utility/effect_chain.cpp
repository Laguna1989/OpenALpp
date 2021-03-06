#include "effect_chain.hpp"

namespace oalpp {
namespace effects {
namespace utility {

EffectChain::EffectChain(
    std::vector<std::reference_wrapper<oalpp::effects::MonoEffectInterface>>& effects)
    : m_effects { effects }
{
}

std::vector<float> EffectChain::process(std::vector<float> const& input)
{
    auto result = input;
    for (auto effect : m_effects) {
        result = effect.get().process(result);
    }
    return result;
}

} // namespace utility
} // namespace effects
} // namespace oalpp
