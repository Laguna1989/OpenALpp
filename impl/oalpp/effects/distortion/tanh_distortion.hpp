#ifndef OPENALPP_EFFECTS_DISTORTION_TANH_DISTORTION_HPP
#define OPENALPP_EFFECTS_DISTORTION_TANH_DISTORTION_HPP

#include <oalpp/effects/mono_effect_interface.hpp>

namespace oalpp {
namespace effects {
namespace distortion {

class TanhDistortion : public MonoEffectInterface {
public:
    TanhDistortion(float preGain, float postGain);
    std::vector<float> process(std::vector<float> const& input) override;

private:
    float m_preGain { 1.0f };
    float m_postGain { 1.0f };
};

} // namespace distortion
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_DISTORTION_TANH_DISTORTION_HPP
