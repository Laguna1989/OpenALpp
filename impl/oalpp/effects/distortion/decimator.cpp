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
    m_y = 0.0f;

    m_counter += m_rate;
    if (m_counter >= 1) {
        m_counter -= 1;
        m_y = (long int)(input * m_m) / (float)m_m;
    }
    return m_y;
}
void Decimator::reset() { }

} // namespace distortion
} // namespace effects
} // namespace oalpp
