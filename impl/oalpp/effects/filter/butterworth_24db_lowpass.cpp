#include "butterworth_24db_lowpass.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace oalpp {
namespace effects {
namespace filter {

Butterworth24dbLowpass::Butterworth24dbLowpass(int sampleRate, float cutoffFrequency, float quality)
{
    if (sampleRate <= 0) [[unlikely]] {
        throw std::invalid_argument { "Sample rate has to be positive" };
    }

    if (cutoffFrequency <= 0 || cutoffFrequency > static_cast<float>(sampleRate)) [[unlikely]] {
        throw std::invalid_argument {
            "Cutoff frequency has to be positive and less than the sample rate"
        };
    }

    setSampleRate(static_cast<float>(sampleRate));
    setParameters(cutoffFrequency, quality);
}

void Butterworth24dbLowpass::setSampleRate(float sampleRate)
{
    m_t0 = 4.0f * sampleRate * sampleRate;
    m_t1 = 8.0f * sampleRate * sampleRate;
    m_t2 = 2.0f * sampleRate;
    m_t3 = 3.141592f / sampleRate;
}

void Butterworth24dbLowpass::setParameters(float cutoffFrequency, float q)
{
    if (q < 0.0f) [[unlikely]] {
        q = 0.0f;
    } else if (q > 1.0f) {
        q = 1.0f;
    }

    float const wp = m_t2 * tanf(m_t3 * cutoffFrequency);

    q *= 6.0f;
    q += 1.0f;

    float b1 = (0.765367f / q) / wp;
    float const b2 = 1.0f / (wp * wp);
    float const bd_tmp = m_t0 * b2 + 1.0f;
    float bd = 1.0f / (bd_tmp + m_t2 * b1);

    m_gain = bd * 0.5f;

    m_coefficient3 = (2.0f - m_t1 * b2);

    m_coefficient1 = m_coefficient3 * bd;
    m_coefficient2 = (bd_tmp - m_t2 * b1) * bd;

    b1 = (1.847759f / q) / wp;

    bd = 1.0f / (bd_tmp + m_t2 * b1);

    m_gain *= bd;
    m_coefficient3 *= bd;
    m_coefficient4 = (bd_tmp - m_t2 * b1) * bd;
}

std::vector<float> Butterworth24dbLowpass::process(std::vector<float> const& input)
{
    std::vector<float> result;
    result.resize(input.size());

    float history1 { 0.0f };
    float history2 { 0.0f };
    float history3 { 0.0f };
    float history4 { 0.0f };

    std::transform(input.cbegin(), input.cend(), result.begin(),
        [this, &history1, &history2, &history3, &history4](float v) {
            float output = (v * m_gain) - (history1 * m_coefficient1);
            float newHist = output - history2 * m_coefficient2;

            output = newHist + history1 * 2.0f;
            output += history2;

            history2 = history1;
            history1 = newHist;

            output -= history3 * m_coefficient3;
            newHist = output - history4 * m_coefficient4;

            output = newHist + history3 * 2.0f;
            output += history4;

            history4 = history3;
            history3 = newHist;

            return output;
        });

    return result;
}

} // namespace filter
} // namespace effects
} // namespace oalpp
