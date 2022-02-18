#include "phase_flip.hpp"
#include <algorithm>

namespace oalpp {
namespace effects {
namespace utility {

std::vector<float> PhaseFlip::process(std::vector<float> const& input)
{
    std::vector<float> result;
    result.resize(input.size());
    std::transform(input.cbegin(), input.cend(), result.begin(), [](float v) { return -v; });
    return result;
}

} // namespace utility
} // namespace effects
} // namespace oalpp
