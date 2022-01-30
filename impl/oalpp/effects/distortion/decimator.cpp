#include "decimator.hpp"
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

float Decimator::process(float input)
{
    m_counter += m_rate;
    if (m_counter >= 1) {
        m_counter -= 1;
        m_returnValue = static_cast<float>(static_cast<long>(input * static_cast<float>(m_m)))
            / static_cast<float>(m_m);
    }
    return m_returnValue;
}

void Decimator::reset() { m_counter = 0.0f; }

} // namespace distortion
} // namespace effects
} // namespace oalpp
