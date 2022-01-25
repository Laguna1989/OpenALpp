#ifndef OPENALPP_EFFECTS_FILTER_RANDOM_LOWPASS_HPP
#define OPENALPP_EFFECTS_FILTER_RANDOM_LOWPASS_HPP

#include "oalpp/effects/mono_effect_interface.hpp"

namespace oalpp {
namespace effects {
namespace filter {

class RandomLowpass : public MonoEffectInterface {
public:
    RandomLowpass(float f, float r, float sample_rate);
    float process(float input) override;

private:
    float r;
    float f;
    float sample_rate;
    float m_c;
    float m_a1;
    float m_a2;
    float m_a3;
    float m_b1;
    float m_b2;

    float m_history1;
    float m_history2;
    float m_history3;
    float m_history4;
};
} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_FILTER_RANDOM_LOWPASS_HPP
