#include "simple_lowpass.hpp"
#include <cmath>
#include <stdexcept>

namespace oalpp {
namespace effects {
namespace filter {

SimpleLowpass::SimpleLowpass(int sampleRate, float cutoffFrequency, float resonance)
{
    if (sampleRate <= 0) {
        throw std::invalid_argument { "Sample rate has to be positive" };
    }

    if (cutoffFrequency <= 0 || cutoffFrequency > static_cast<float>(sampleRate)) {
        throw std::invalid_argument {
            "Cutoff frequency has to be positive and less than the sample rate"
        };
    }

    m_c = 1.0f / tan(3.141592f * cutoffFrequency / static_cast<float>(sampleRate));

    m_a1 = 1.0f / (1.0f + resonance * m_c + m_c * m_c);
    m_a2 = 2.0f * m_a1;
    m_a3 = m_a1;
    m_b1 = 2.0f * (1.0f - m_c * m_c) * m_a1;
    m_b2 = (1.0f - resonance * m_c + m_c * m_c) * m_a1;
}

float SimpleLowpass::process(float input)
{
    auto out = m_a1 * input + m_a2 * m_history1 + m_a3 * m_history2 - m_b1 * m_history3
        - m_b2 * m_history4;

    m_history4 = m_history3;
    m_history3 = out;
    m_history2 = m_history1;
    m_history1 = input;

    return out;
}
void SimpleLowpass::reset()
{
    m_history1 = 0.0f;
    m_history2 = 0.0f;
    m_history3 = 0.0f;
    m_history4 = 0.0f;
}

} // namespace filter
} // namespace effects
} // namespace oalpp
