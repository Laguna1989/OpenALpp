#include "approval_test_helpers.hpp"

int ApprovalTestHelpers::asInt(float number, unsigned int digits)
{
    return static_cast<int>(number * digits);
}
