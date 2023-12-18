#ifndef OPENALPP_EFFECTS_FILTER_SIMPLE_LOWPASS_HPP
#define OPENALPP_EFFECTS_FILTER_SIMPLE_LOWPASS_HPP

#include <oalpp/effects/mono_effect_interface.hpp>

namespace oalpp {
namespace effects {
namespace filter {

class SimpleLowpass : public MonoEffectInterface {
public:
    ///
    /// \param sampleRate Sample rate must be positive
    /// \param cutoffFrequency Cutoff frequency must be positive and less than sample rate
    /// \param resonance Resonance value should roughly be between 0.2 and 1.5
    SimpleLowpass(int sampleRate, float cutoffFrequency, float resonance);
    std::vector<float> process(std::vector<float> const& input) override;

private:
    float m_c { 0.0f };

    float m_a1 { 0.0f };
    float m_a2 { 0.0f };
    float m_a3 { 0.0f };
    float m_b1 { 0.0f };
    float m_b2 { 0.0f };
};

} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_FILTER_SIMPLE_LOWPASS_HPP
