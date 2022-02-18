#ifndef OPENALPP_EFFECTS_DISTORTION_DECIMATOR_HPP
#define OPENALPP_EFFECTS_DISTORTION_DECIMATOR_HPP

#include "oalpp/effects/mono_effect_bulk.hpp"

namespace oalpp {
namespace effects {
namespace distortion {

class Decimator : public MonoEffectBulk {
public:
    Decimator(int bits, float rate);
    std::vector<float> process(std::vector<float> const& input) override;

private:
    float m_rate { 1.0f };
    long int m_m { 0 };
};

} // namespace distortion
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_DISTORTION_DECIMATOR_HPP
