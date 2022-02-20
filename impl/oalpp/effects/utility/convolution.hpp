#ifndef OPENALPP_CONVOLUTION_HPP
#define OPENALPP_CONVOLUTION_HPP

#include "oalpp/effects/mono_effect_interface.hpp"
#include <complex>
#include <vector>

namespace oalpp {
namespace effects {
namespace utility {

class Convolution : public MonoEffectInterface {
public:
    explicit Convolution(std::vector<float> const& kernel);

    std::vector<float> process(std::vector<float> const& input) override;

private:
    std::vector<std::complex<float>> m_kernel {};
};

} // namespace utility
} // namespace effects
} // namespace oalpp

#endif // OPENALPP_CONVOLUTION_HPP
