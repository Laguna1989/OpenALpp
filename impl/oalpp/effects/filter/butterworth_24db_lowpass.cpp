#include "butterworth_24db_lowpass.hpp"
#include <math.h>

namespace oalpp {
namespace effects {
namespace filter {

Butterworth24dbLowpass::Butterworth24dbLowpass(int sampleRate, float cutoffFrequency, float q)
{
    setSampleRate(static_cast<float>(sampleRate));
    set(cutoffFrequency, q);
}

void Butterworth24dbLowpass::setSampleRate(float sampleRate)
{
    float pi = 4.f * atanf(1.f);

    m_t0 = 4.f * sampleRate * sampleRate;
    m_t1 = 8.f * sampleRate * sampleRate;
    m_t2 = 2.f * sampleRate;
    m_t3 = pi / sampleRate;

    m_minCutoff = sampleRate * 0.01f;
    m_maxCutoff = sampleRate * 0.45f;
}

void Butterworth24dbLowpass::set(float cutoffFrequency, float q)
{
    if (cutoffFrequency < m_minCutoff) {
        cutoffFrequency = m_minCutoff;
    } else if (cutoffFrequency > m_maxCutoff) {
        cutoffFrequency = m_maxCutoff;
    }

    if (q < 0.f) {
        q = 0.f;
    } else if (q > 1.f) {
        q = 1.f;
    }

    float wp = m_t2 * tanf(m_t3 * cutoffFrequency);
    float bd, bd_tmp, b1, b2;

    q *= 6.f;
    q += 1.f;

    b1 = (0.765367f / q) / wp;
    b2 = 1.f / (wp * wp);

    bd_tmp = m_t0 * b2 + 1.f;

    bd = 1.f / (bd_tmp + m_t2 * b1);

    m_gain = bd * 0.5f;

    m_coefficient2 = (2.f - m_t1 * b2);

    m_coefficient0 = m_coefficient2 * bd;
    m_coefficient1 = (bd_tmp - m_t2 * b1) * bd;

    b1 = (1.847759f / q) / wp;

    bd = 1.f / (bd_tmp + m_t2 * b1);

    m_gain *= bd;
    m_coefficient2 *= bd;
    m_coefficient3 = (bd_tmp - m_t2 * b1) * bd;
}

float Butterworth24dbLowpass::process(float input)
{
    float output = input * m_gain;
    float new_hist;

    output -= m_history1 * m_coefficient0;
    new_hist = output - m_history2 * m_coefficient1;

    output = new_hist + m_history1 * 2.f;
    output += m_history2;

    m_history2 = m_history1;
    m_history1 = new_hist;

    output -= m_history3 * m_coefficient2;
    new_hist = output - m_history4 * m_coefficient3;

    output = new_hist + m_history3 * 2.f;
    output += m_history4;

    m_history4 = m_history3;
    m_history3 = new_hist;

    return output;
}

} // namespace filter
} // namespace effects

} // namespace oalpp
