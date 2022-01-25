#ifndef OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP
#define OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP

#include "oalpp/effects/mono_effect_interface.hpp"

namespace oalpp {
namespace effects {
namespace filter {

class FilterButterworth24db : public oalpp::effects::MonoEffectInterface {
public:
    FilterButterworth24db();
    void setSampleRate(float fs);
    void set(float cutoff, float q);
    float process(float input) override;

private:
    float t0, t1, t2, t3;
    float coef0, coef1, coef2, coef3;
    float history1, history2, history3, history4;
    float gain;
    float min_cutoff, max_cutoff;
};

} // namespace filter
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_EFFECTS_FILTER_BUTTERWORTH_24_D_B_HPP
