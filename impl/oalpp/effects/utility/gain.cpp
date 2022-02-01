#include "gain.hpp"

namespace oalpp {
namespace effects {
namespace utility {

Gain::Gain(float gain)
    : m_gain { gain }
{
}

float Gain::process(float input) { return input * m_gain; }

void Gain::reset() { }

} // namespace utility
} // namespace effects
} // namespace oalpp
