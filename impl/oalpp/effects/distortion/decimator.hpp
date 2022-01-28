#ifndef OPENALPP_EFFECTS_OTHER_DECIMATOR_HPP
#define OPENALPP_EFFECTS_OTHER_DECIMATOR_HPP

#include "oalpp/effects/mono_effect_interface.hpp"

namespace oalpp {
namespace effects {
namespace distortion {

class Decimator : public MonoEffectInterface {
public:
    Decimator(int bits, float rate);

    float process(float input) override;
    void reset() override;

private:
    float m_rate { 1.0f };

    long int m_m { 0 };
    float m_y = 0.0f;
    float m_counter = 0.0f;
};

} // namespace distortion
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_OTHER_DECIMATOR_HPP
