#include "simple_highpass.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace oalpp {
namespace effects {
namespace filter {

SimpleHighpass::SimpleHighpass(int sampleRate, float cutoffFrequency, float resonance)
{
    if (sampleRate <= 0) {
        throw std::invalid_argument { "Sample rate has to be positive" };
    }

    if (cutoffFrequency <= 0 || cutoffFrequency > static_cast<float>(sampleRate)) {
        throw std::invalid_argument {
            "Cutoff frequency has to be positive and less than the sample rate"
        };
    }

    m_c = tan(3.141592f * cutoffFrequency / static_cast<float>(sampleRate));

    m_a1 = 1.0f / (1.0f + resonance * m_c + m_c * m_c);
    m_a2 = -2.0f * m_a1;
    m_a3 = m_a1;
    m_b1 = 2.0f * (m_c * m_c - 1.0f) * m_a1;
    m_b2 = (1.0f - resonance * m_c + m_c * m_c) * m_a1;
}

std::vector<float> SimpleHighpass::process(std::vector<float> const& input)
{
    std::vector<float> result;
    result.resize(input.size());

    float history1 { 0.0f };
    float history2 { 0.0f };
    float history3 { 0.0f };
    float history4 { 0.0f };

    std::transform(input.cbegin(), input.cend(), result.begin(),
        [this, &history1, &history2, &history3, &history4](float v) {
            auto const out
                = m_a1 * v + m_a2 * history1 + m_a3 * history2 - m_b1 * history3 - m_b2 * history4;

            history4 = history3;
            history3 = out;
            history2 = history1;
            history1 = v;

            return out;
        });

    return result;
}

} // namespace filter
} // namespace effects
} // namespace oalpp
