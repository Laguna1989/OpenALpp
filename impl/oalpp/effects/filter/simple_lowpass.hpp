#ifndef OPENALPP_EFFECTS_FILTER_SIMPLE_LOWPASS_HPP
#define OPENALPP_EFFECTS_FILTER_SIMPLE_LOWPASS_HPP

#include "oalpp/effects/mono_effect_interface.hpp"

namespace oalpp {
namespace effects {
namespace filter {

class SimpleLowpass : public MonoEffectInterface {
public:
    SimpleLowpass(float f, float r, float sample_rate);
    float process(float input) override;
    void reset() override;

private:
    float r { 0.0f };
    float f { 0.0f };
    float sample_rate { 0.0f };

    float m_c { 0.0f };

    float m_a1 { 0.0f };
    float m_a2 { 0.0f };
    float m_a3 { 0.0f };
    float m_b1 { 0.0f };
    float m_b2 { 0.0f };

    float m_history1 { 0.0f };
    float m_history2 { 0.0f };
    float m_history3 { 0.0f };
    float m_history4 { 0.0f };
};

} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_FILTER_SIMPLE_LOWPASS_HPP
