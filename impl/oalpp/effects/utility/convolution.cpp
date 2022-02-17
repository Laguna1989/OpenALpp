#include "convolution.hpp"
#include "dj_fft.h"
#include <algorithm>
#include <iostream>

namespace oalpp {
namespace effects {
namespace utility {

namespace {
std::vector<std::complex<float>> real2Complex(std::vector<float> const& realValues)
{
    std::vector<std::complex<float>> complexValues;
    std::transform(
        realValues.begin(), realValues.end(), std::back_inserter(complexValues), [](float v) {
            return std::complex<float> { v, 0.0f };
        });
    return complexValues;
}

std::vector<float> complex2real(std::vector<std::complex<float>> const& complexValues)
{
    float const gainFactor = 2.0f / sqrt(2.0f);
    std::vector<float> realValues;
    std::transform(complexValues.begin(), complexValues.end(), std::back_inserter(realValues),
        [gainFactor](std::complex<float> c) { return c.real() * gainFactor; });
    return realValues;
}

std::size_t getNextNSquare(std::size_t size)
{
    auto sizeN2 = 2;
    while (sizeN2 < size) {
        sizeN2 *= 2;
    }
    return sizeN2;
}

std::vector<std::complex<float>> doFFT(std::vector<float> samples)
{
    std::vector<std::complex<float>> samplesComplex = real2Complex(samples);
    samplesComplex.resize(getNextNSquare(samplesComplex.size()));
    return dj::fft1d(samplesComplex, dj::fft_dir::DIR_BWD);
}

std::vector<float> doFFT(std::vector<std::complex<float>> samples)
{
    -auto const transformed = dj::fft1d(samples, dj::fft_dir::DIR_FWD);
    return complex2real(transformed);
}

} // namespace

Convolution::Convolution(std::vector<float> const& kernel)
    : m_kernel { doFFT(kernel) }
{
}

std::vector<float> Convolution::process(std::vector<float> const& input)
{
    auto inputTransformed = doFFT(input);
    unsigned int biggerSize = std::max(inputTransformed.size(), m_kernel.size());

    std::vector<std::complex<float>> multipliedTransformed;
    multipliedTransformed.resize(biggerSize);

    for (auto i = 0U; i != biggerSize; ++i) {
        auto const kernelValue = i < m_kernel.size() ? m_kernel[i] : 0.0f;
        auto const inputValue = i < inputTransformed.size() ? inputTransformed[i] : 0.0f;
        multipliedTransformed[i] = kernelValue * inputValue;
    }

    return doFFT(multipliedTransformed);
}

} // namespace utility
} // namespace effects
} // namespace oalpp
