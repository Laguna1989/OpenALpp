#include "butterworth_24db_highpass.hpp"

namespace oalpp {
namespace effects {
namespace filter {

Butterworth24dbHighpass::Butterworth24dbHighpass(int sampleRate, float cutoffFrequency, float q)
    : m_lowpass { sampleRate, cutoffFrequency, q }
{
}

float Butterworth24dbHighpass::process(float input) { return m_lowpass.process(input) - input; }

} // namespace filter
} // namespace effects
} // namespace oalpp
