#ifndef OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP
#define OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP

#include "oalpp/effects/mono_effect_interface.hpp"

namespace oalpp {
namespace effects {
namespace filter {

class Butterworth24dbLowpass : public oalpp::effects::MonoEffectInterface {
public:
    Butterworth24dbLowpass(int sampleRate, float cutoffFrequency, float q);
    float process(float input) override;
    void reset() override;

private:
    void setSampleRate(float sampleRate);
    void set(float cutoffFrequency, float q);

    float m_t0 { 0.0f };
    float m_t1 { 0.0f };
    float m_t2 { 0.0f };
    float m_t3 { 0.0f };

    float m_coefficient0 { 0.0f };
    float m_coefficient1 { 0.0f };
    float m_coefficient2 { 0.0f };
    float m_coefficient3 { 0.0f };

    float m_history1 { 0.0f };
    float m_history2 { 0.0f };
    float m_history3 { 0.0f };
    float m_history4 { 0.0f };

    float m_gain { 0.0f };
    float m_minCutoff { 0.0f };
    float m_maxCutoff { 0.0f };
};

} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP
