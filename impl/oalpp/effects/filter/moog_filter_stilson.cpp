#include "moog_filter_stilson.hpp"
#include <algorithm>
#include <cmath>

namespace {

float S_STILSON_GAINTABLE[199] = { 0.999969f, 0.990082f, 0.980347f, 0.970764f, 0.961304f, 0.951996f,
    0.94281f, 0.933777f, 0.924866f, 0.916077f, 0.90741f, 0.898865f, 0.890442f, 0.882141f, 0.873962f,
    0.865906f, 0.857941f, 0.850067f, 0.842346f, 0.834686f, 0.827148f, 0.819733f, 0.812378f,
    0.805145f, 0.798004f, 0.790955f, 0.783997f, 0.77713f, 0.770355f, 0.763672f, 0.75708f, 0.75058f,
    0.744141f, 0.737793f, 0.731537f, 0.725342f, 0.719238f, 0.713196f, 0.707245f, 0.701355f,
    0.695557f, 0.689819f, 0.684174f, 0.678558f, 0.673035f, 0.667572f, 0.66217f, 0.65686f, 0.651581f,
    0.646393f, 0.641235f, 0.636169f, 0.631134f, 0.62619f, 0.621277f, 0.616425f, 0.611633f,
    0.606903f, 0.602234f, 0.597626f, 0.593048f, 0.588531f, 0.584045f, 0.579651f, 0.575287f,
    0.570953f, 0.566681f, 0.562469f, 0.558289f, 0.554169f, 0.550079f, 0.546051f, 0.542053f,
    0.538116f, 0.53421f, 0.530334f, 0.52652f, 0.522736f, 0.518982f, 0.515289f, 0.511627f, 0.507996f,
    0.504425f, 0.500885f, 0.497375f, 0.493896f, 0.490448f, 0.487061f, 0.483704f, 0.480377f,
    0.477081f, 0.473816f, 0.470581f, 0.467377f, 0.464203f, 0.46109f, 0.457977f, 0.454926f,
    0.451874f, 0.448883f, 0.445892f, 0.442932f, 0.440033f, 0.437134f, 0.434265f, 0.431427f,
    0.428619f, 0.425842f, 0.423096f, 0.42038f, 0.417664f, 0.415009f, 0.412354f, 0.409729f,
    0.407135f, 0.404572f, 0.402008f, 0.399506f, 0.397003f, 0.394501f, 0.392059f, 0.389618f,
    0.387207f, 0.384827f, 0.382477f, 0.380127f, 0.377808f, 0.375488f, 0.37323f, 0.370972f,
    0.368713f, 0.366516f, 0.364319f, 0.362122f, 0.359985f, 0.357849f, 0.355713f, 0.353607f,
    0.351532f, 0.349457f, 0.347412f, 0.345398f, 0.343384f, 0.34137f, 0.339417f, 0.337463f, 0.33551f,
    0.333588f, 0.331665f, 0.329773f, 0.327911f, 0.32605f, 0.324188f, 0.322357f, 0.320557f,
    0.318756f, 0.316986f, 0.315216f, 0.313446f, 0.311707f, 0.309998f, 0.308289f, 0.30658f,
    0.304901f, 0.303223f, 0.301575f, 0.299927f, 0.298309f, 0.296692f, 0.295074f, 0.293488f,
    0.291931f, 0.290375f, 0.288818f, 0.287262f, 0.285736f, 0.284241f, 0.282715f, 0.28125f,
    0.279755f, 0.27829f, 0.276825f, 0.275391f, 0.273956f, 0.272552f, 0.271118f, 0.269745f,
    0.268341f, 0.266968f, 0.265594f, 0.264252f, 0.262909f, 0.261566f, 0.260223f, 0.258911f,
    0.257599f, 0.256317f, 0.255035f, 0.25375f };

float saturate(float sample)
{
    auto x1 = static_cast<float>(std::abs(sample + 0.95f));
    auto x2 = static_cast<float>(std::abs(sample - 0.95f));
    return 0.5f * (x1 - x2);
}
} // namespace

oalpp::effects::filter::MoogFilterStilson::MoogFilterStilson(
    float sampleRate, float cutoff, float resonance)
    : m_resonance { resonance }
    , m_cutoff { cutoff }
    , m_sampleRate { sampleRate }
{
    setCutoff();
    setResonance();
}

std::vector<float> oalpp::effects::filter::MoogFilterStilson::process(
    const std::vector<float>& input)
{
    std::vector<float> output;
    output.resize(input.size());
    float localState;

    for (int s = 0; s < input.size(); ++s) {
        // Scale by arbitrary value on account of our saturation function
        float const current_sample = input[s] * 0.65f;

        // Negative Feedback
        m_output = 0.25f * (current_sample - m_output);

        for (int pole = 0; pole < 4; ++pole) {
            localState = m_state[pole];
            m_output = saturate(m_output + m_p * (m_output - localState));
            m_state[pole] = m_output;
            m_output = saturate(m_output + localState);
        }
        // TODO
        //        SNAP_TO_ZERO(m_output);
        output[s] = m_output;
        m_output *= m_q; // Scale stateful output by Q
    }

    return output;
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

void oalpp::effects::filter::MoogFilterStilson::setResonance()
{
    m_resonance = std::min(m_resonance, 1.0f);

    float ix = m_p * 99;
    int ixInt = static_cast<int>(std::floor(ix));
    float ixFrac = ix - ixInt;

    m_q = m_resonance * (1.0f - ixFrac) * S_STILSON_GAINTABLE[ixInt + 99]
        + ixFrac * S_STILSON_GAINTABLE[ixInt + 100];
}
