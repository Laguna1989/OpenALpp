#ifndef OPENALPP_BUTTERWORTH_24_D_B_HIGHPASS_HPP
#define OPENALPP_BUTTERWORTH_24_D_B_HIGHPASS_HPP

#include "oalpp/effects/filter/random_lowpass.hpp"
#include "oalpp/effects/mono_effect_interface.hpp"

namespace oalpp {
namespace effects {
namespace filter {

class Butterworth24dbHighpass : public oalpp::effects::MonoEffectInterface {
public:
    Butterworth24dbHighpass(int sampleRate, float cutoffFrequency, float q);

    float process(float input) override;
    void reset() override;

private:
    RandomLowpass m_lowpass;
};

} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_BUTTERWORTH_24_D_B_HIGHPASS_HPP
