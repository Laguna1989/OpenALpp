#include "tanh_distortion.hpp"
#include <cmath>

namespace oalpp {
namespace effects {
namespace distortion {

TanhDistortion::TanhDistortion(float preGain, float postGain)
    : m_preGain { preGain }
    , m_postGain { postGain }
{
}

float TanhDistortion::process(float input) { return tanh(input * m_preGain) * m_postGain; }
void TanhDistortion::reset() { }

} // namespace distortion
} // namespace effects
} // namespace oalpp
