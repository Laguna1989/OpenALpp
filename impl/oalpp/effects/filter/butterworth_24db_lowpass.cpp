#include "butterworth_24db_lowpass.hpp"
#include <cmath>
#include <stdexcept>

namespace oalpp {
namespace effects {
namespace filter {

Butterworth24dbLowpass::Butterworth24dbLowpass(int sampleRate, float cutoffFrequency, float quality)
{
    if (sampleRate <= 0) {
        throw std::invalid_argument { "Sample rate has to be positive" };
    }

    if (cutoffFrequency <= 0 || cutoffFrequency > static_cast<float>(sampleRate)) {
        throw std::invalid_argument {
            "Cutoff frequency has to be positive and less than the sample rate"
        };
    }

    setSampleRate(static_cast<float>(sampleRate));
    set(cutoffFrequency, quality);
}

void Butterworth24dbLowpass::setSampleRate(float sampleRate)
{
    m_t0 = 4.0f * sampleRate * sampleRate;
    m_t1 = 8.0f * sampleRate * sampleRate;
    m_t2 = 2.0f * sampleRate;
    m_t3 = 3.141592f / sampleRate;
}

void Butterworth24dbLowpass::set(float cutoffFrequency, float q)
{
    if (q < 0.0f) {
        q = 0.0f;
    } else if (q > 1.0f) {
        q = 1.0f;
    }

    float const wp = m_t2 * tanf(m_t3 * cutoffFrequency);

    q *= 6.0f;
    q += 1.0f;

    float b1 = (0.765367f / q) / wp;
    float b2 = 1.0f / (wp * wp);
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

float Butterworth24dbLowpass::process(float input)
{
    float output = (input * m_gain) - (m_history1 * m_coefficient1);
    float newHist = output - m_history2 * m_coefficient2;

    output = newHist + m_history1 * 2.0f;
    output += m_history2;

    m_history2 = m_history1;
    m_history1 = newHist;

    output -= m_history3 * m_coefficient3;
    newHist = output - m_history4 * m_coefficient4;

    output = newHist + m_history3 * 2.0f;
    output += m_history4;

    m_history4 = m_history3;
    m_history3 = newHist;

    return output;
}

void Butterworth24dbLowpass::reset()
{
    m_history1 = 0.0f;
    m_history2 = 0.0f;
    m_history3 = 0.0f;
    m_history4 = 0.0f;
}

} // namespace filter
} // namespace effects
} // namespace oalpp
