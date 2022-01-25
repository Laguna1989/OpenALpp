#ifndef OPENALPP_BUTTERWORTH_24_D_B_HIGHPASS_HPP
#define OPENALPP_BUTTERWORTH_24_D_B_HIGHPASS_HPP

#include "oalpp/effects/filter/butterworth_24db_lowpass.hpp"
#include "oalpp/effects/mono_effect_interface.hpp"
namespace oalpp {
namespace effects {
namespace filter {

class Butterworth24dbHighpass : public oalpp::effects::MonoEffectInterface {
public:
    Butterworth24dbHighpass(int sampleRate, float cutoffFrequency, float q);

    float process(float input) override;

private:
    Butterworth24dbLowpass m_lowpass;
};

} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_BUTTERWORTH_24_D_B_HIGHPASS_HPP
