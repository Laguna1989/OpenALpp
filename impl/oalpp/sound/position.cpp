#include "position.hpp"

namespace oalpp {

bool operator==(Position const& lhs, Position const& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

} // namespace oalpp
