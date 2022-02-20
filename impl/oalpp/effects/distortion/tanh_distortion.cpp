#include "tanh_distortion.hpp"
#include <algorithm>
#include <cmath>

namespace oalpp {
namespace effects {
namespace distortion {

TanhDistortion::TanhDistortion(float preGain, float postGain)
    : m_preGain { preGain }
    , m_postGain { postGain }
{
}

std::vector<float> TanhDistortion::process(std::vector<float> const& input)
{
    std::vector<float> result;
    result.resize(input.size());
    std::transform(input.cbegin(), input.cend(), result.begin(),
        [pre = m_preGain, post = m_postGain](float v) { return tanh(v * pre) * post; });
    return result;
}

} // namespace distortion
} // namespace effects
} // namespace oalpp
