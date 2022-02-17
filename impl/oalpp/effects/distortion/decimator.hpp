#ifndef OPENALPP_EFFECTS_DISTORTION_DECIMATOR_HPP
#define OPENALPP_EFFECTS_DISTORTION_DECIMATOR_HPP

#include "oalpp/effects/mono_effect_iterative.hpp"

namespace oalpp {
namespace effects {
namespace distortion {

class Decimator : public MonoEffectIterative {
public:
    Decimator(int bits, float rate);

    float process(float input) override;
    void reset() override;

private:
    float m_rate { 1.0f };
    float m_returnValue { 0.0f };
    long int m_m { 0 };
    float m_counter { 0.0f };
};

} // namespace distortion
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_DISTORTION_DECIMATOR_HPP
