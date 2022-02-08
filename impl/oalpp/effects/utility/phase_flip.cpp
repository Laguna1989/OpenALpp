#include "phase_flip.hpp"

namespace oalpp {
namespace effects {
namespace utility {
float PhaseFlip::process(float input) { return -input; }
void PhaseFlip::reset() { }

} // namespace utility
} // namespace effects
} // namespace oalpp