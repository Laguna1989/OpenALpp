#include "decimator.hpp"
#include <algorithm>
#include <stdexcept>

namespace oalpp {
namespace effects {
namespace distortion {

Decimator::Decimator(int bits, float rate)
    : m_rate { rate }
{
    if (m_rate <= 0.0f || m_rate > 1.0f) {
        throw std::invalid_argument { "Rate must be in the range of ]0.0, 1.0]" };
    }

    if (bits < 1) {
        throw std::invalid_argument { "Bits must be greater than zero" };
    }

    m_m = 1 << (bits - 1);
}
std::vector<float> Decimator::process(std::vector<float> const& input)
{
    std::vector<float> result;
    result.resize(input.size());

    float counter = 0.0f;
    float lastReturnValue = 0.0f;

    std::transform(input.cbegin(), input.cend(), result.begin(),
        [&counter, &lastReturnValue, rate = m_rate, m = m_m](float v) {
            counter += rate;
            if (counter >= 1) {
                counter -= 1;
                lastReturnValue = static_cast<float>(static_cast<long>(v * static_cast<float>(m)))
                    / static_cast<float>(m);
            }
            return lastReturnValue;
        });

    return result;
}

} // namespace distortion
} // namespace effects
} // namespace oalpp
