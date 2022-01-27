#include "butterworth_24db_highpass.hpp"

namespace oalpp {
namespace effects {
namespace filter {

Butterworth24dbHighpass::Butterworth24dbHighpass(int sampleRate, float cutoffFrequency, float q)
    : m_lowpass { cutoffFrequency, q, static_cast<float>(sampleRate) }
{
}

float Butterworth24dbHighpass::process(float input) { return input - m_lowpass.process(input); }
void Butterworth24dbHighpass::reset() { m_lowpass.reset(); }

} // namespace filter
} // namespace effects
} // namespace oalpp
