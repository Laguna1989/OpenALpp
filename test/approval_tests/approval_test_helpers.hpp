#ifndef OPENALPP_APPROVAL_TEST_HELPERS_HPP
#define OPENALPP_APPROVAL_TEST_HELPERS_HPP

#include <vector>

struct ApprovalTestHelpers {
    static std::vector<int> asInt(std::vector<float> const& number, unsigned int digits);
};

#endif // OPENALPP_APPROVAL_TEST_HELPERS_HPP
