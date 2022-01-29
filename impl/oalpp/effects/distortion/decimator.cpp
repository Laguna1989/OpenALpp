#include "decimator.hpp"

namespace oalpp {
namespace effects {
namespace distortion {

Decimator::Decimator(int bits, float rate)
    : m_rate { rate }
{
    m_m = 1 << (bits - 1);
}

float Decimator::process(float input)
{

    m_counter += m_rate;
    if (m_counter >= 1) {
        m_counter -= 1;
        m_returnValue = (long int)(input * m_m) / (float)m_m;
    }
    return m_returnValue;
}
void Decimator::reset() { m_counter = 0.0f; }

} // namespace distortion
} // namespace effects
} // namespace oalpp
