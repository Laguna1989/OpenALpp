#include "moog_filter_stilson.hpp"

oalpp::effects::filter::MoogFilterStilson::MoogFilterStilson(float resonance, float cutoff)
    : m_resonance { resonance }
    , m_cutoff { cutoff }
{
    setCutoff();
    setResonance();
}

std::vector<float> oalpp::effects::filter::MoogFilterStilson::process(
    const std::vector<float>& input)
{
    return std::vector<float>();
}

void oalpp::effects::filter::MoogFilterStilson::setCutoff()
{
    // Normalized cutoff between [0, 1]
    float fc = (m_cutoff) / m_sampleRate;
    float x2 = fc * fc;
    float x3 = fc * fc * fc;

    // Frequency & amplitude correction (Cubic Fit)
    m_p = -0.69346f * x3 - 0.59515f * x2 + 3.2937f * fc - 1.0072f;
}

void oalpp::effects::filter::MoogFilterStilson::setResonance() { }
