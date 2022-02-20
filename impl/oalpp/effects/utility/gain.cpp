#include "gain.hpp"
#include <algorithm>

namespace oalpp {
namespace effects {
namespace utility {

Gain::Gain(float gain)
    : m_gain { gain }
{
}

std::vector<float> Gain::process(std::vector<float> const& input)
{
    std::vector<float> results;
    results.resize(input.size());
    std::transform(input.cbegin(), input.cend(), results.begin(),
        [gain = m_gain](float f) { return f * gain; });
    return results;
}

} // namespace utility
} // namespace effects
} // namespace oalpp
