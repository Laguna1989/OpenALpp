#include "approval_test_helpers.hpp"
#include <algorithm>

std::vector<int> ApprovalTestHelpers::asInt(std::vector<float> const& numbers, unsigned int digits)
{
    std::vector<int> numbersAsInts;
    numbersAsInts.resize(numbers.size());
    std::transform(numbers.cbegin(), numbers.cend(), numbersAsInts.begin(),
        [digits](float number) { return static_cast<int>(number * digits); });
    return numbersAsInts;
}
