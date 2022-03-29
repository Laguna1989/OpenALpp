#ifndef OPENALPP_MOOG_FILTER_STILSON_HPP
#define OPENALPP_MOOG_FILTER_STILSON_HPP

#include "oalpp/effects/mono_effect_interface.hpp"
#include <array>

namespace oalpp {
namespace effects {
namespace filter {

class MoogFilterStilson : public MonoEffectInterface {
public:
    MoogFilterStilson(float resonance, float cutoff, float sampleRate);

    std::vector<float> process(const std::vector<float>& input) override;

private:
    float m_cutoff { 0.0f };
    float m_resonance { 0.0f };
    float m_sampleRate { 0.0f };

    float m_p { 0.0f };
    float m_q { 0.0f };
    std::array<float, 4> m_state;
    float m_output { 0.0f };

    void setCutoff();
    void setResonance();

    float saturate(float sample) const;
};

} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_MOOG_FILTER_STILSON_HPP
