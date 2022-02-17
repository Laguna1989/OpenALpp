#ifndef OPENALPP_EFFECTS_DISTORTION_TANH_DISTORTION_HPP
#define OPENALPP_EFFECTS_DISTORTION_TANH_DISTORTION_HPP

#include "oalpp/effects/mono_effect_iterative.hpp"
namespace oalpp {
namespace effects {
namespace distortion {

class TanhDistortion : public MonoEffectIterative {
public:
    TanhDistortion(float preGain, float postGain);
    float process(float input) override;
    void reset() override;

private:
    float m_preGain { 1.0f };
    float m_postGain { 1.0f };
};

} // namespace distortion
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_DISTORTION_TANH_DISTORTION_HPP
