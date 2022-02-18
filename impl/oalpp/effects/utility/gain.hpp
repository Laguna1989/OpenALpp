#ifndef OPENALPP_EFFECTS_UTILITY_GAIN_HPP
#define OPENALPP_EFFECTS_UTILITY_GAIN_HPP

#include "oalpp/effects/mono_effect_bulk.hpp"

namespace oalpp {
namespace effects {
namespace utility {

class Gain : public oalpp::effects::MonoEffectBulk {
public:
    explicit Gain(float gain);
    std::vector<float> process(std::vector<float> const& input) override;

private:
    float m_gain { 1.0f };
};

} // namespace utility
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_UTILITY_GAIN_HPP
