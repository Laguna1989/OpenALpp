#ifndef OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP
#define OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP

#include "oalpp/effects/mono_effect_interface.hpp"

namespace oalpp {
namespace effects {
namespace filter {

class FilterButterworth24db : public oalpp::effects::MonoEffectInterface {
public:
    FilterButterworth24db(float sampleRate, float cutoffFrequency, float q);
    float process(float input) override;

private:
    void setSampleRate(float sampleRate);
    void set(float cutoffFrequency, float q);

    float m_t0;
    float m_t1;
    float m_t2;
    float m_t3;

    float m_coefficient0;
    float m_coefficient1;
    float m_coefficient2;
    float m_coefficient3;

    float m_history1 { 0.0f };
    float m_history2 { 0.0f };
    float m_history3 { 0.0f };
    float m_history4 { 0.0f };

    float m_gain;
    float m_minCutoff;
    float m_maxCutoff;
};

} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP
