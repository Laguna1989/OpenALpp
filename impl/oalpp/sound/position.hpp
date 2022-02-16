#ifndef OPENALPP_POSITION_HPP
#define OPENALPP_POSITION_HPP

namespace oalpp {

struct Position {
    float x { 0.0f };
    float y { 0.0f };
    float z { 0.0f };
};

bool operator==(Position const& lhs, Position const& rhs);

} // namespace oalpp

#endif // OPENALPP_POSITION_HPP
