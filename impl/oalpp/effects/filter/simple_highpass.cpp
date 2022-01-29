#include "simple_highpass.hpp"
#include <cmath>

namespace oalpp {
namespace effects {
namespace filter {

SimpleHighpass::SimpleHighpass(int sample_rate, float f, float r)
{
    m_c = tan(3.141592f * f / static_cast<float>(sample_rate));

    m_a1 = 1.0f / (1.0f + r * m_c + m_c * m_c);
    m_a2 = -2.0f * m_a1;
    m_a3 = m_a1;
    m_b1 = 2.0f * (m_c * m_c - 1.0f) * m_a1;
    m_b2 = (1.0f - r * m_c + m_c * m_c) * m_a1;
}

float SimpleHighpass::process(float input)
{
    auto out = m_a1 * input + m_a2 * m_history1 + m_a3 * m_history2 - m_b1 * m_history3
        - m_b2 * m_history4;

    m_history4 = m_history3;
    m_history3 = out;
    m_history2 = m_history1;
    m_history1 = input;

    return out;
}
void SimpleHighpass::reset()
{
    m_history1 = 0.0f;
    m_history2 = 0.0f;
    m_history3 = 0.0f;
    m_history4 = 0.0f;
}

} // namespace filter
} // namespace effects
} // namespace oalpp
