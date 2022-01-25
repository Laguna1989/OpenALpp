#include "random_lowpass.hpp"
#include <cmath>

namespace oalpp {
namespace effects {
namespace filter {

RandomLowpass::RandomLowpass(float f, float r, float sample_rate)
{
    m_c = 1.0 / tan(3.141592 * f / sample_rate);

    m_a1 = 1.0 / (1.0 + r * m_c + m_c * m_c);
    m_a2 = 2 * m_a1;
    m_a3 = m_a1;
    m_b1 = 2.0 * (1.0 - m_c * m_c) * m_a1;
    m_b2 = (1.0 - r * m_c + m_c * m_c) * m_a1;
}

float RandomLowpass::process(float input)
{
    auto out = m_a1 * input + m_a2 * m_history1 + m_a3 * m_history2 - m_b1 * m_history3
        - m_b2 * m_history4;

    m_history4 = m_history3;
    m_history3 = out;
    m_history2 = m_history1;
    m_history1 = input;

    return out;
}

} // namespace filter
} // namespace effects
} // namespace oalpp
