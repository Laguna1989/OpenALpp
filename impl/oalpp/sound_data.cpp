#include "sound_data.hpp"
#include "libnyquist/Decoders.h"
#include <utility>

namespace oalpp {

SoundData::SoundData(std::string const& fileName)
{
    auto fileData = std::make_unique<nqr::AudioData>();
    nqr::NyquistIO loader;
    loader.Load(fileData.get(), fileName);

    m_channels = fileData->channelCount;
    m_sampleRate = fileData->sampleRate;
    m_samples = std::move(fileData->samples);
}

int SoundData::getNumberOfChannels() const { return m_channels; }

int SoundData::getSampleRate() const { return m_sampleRate; }

std::vector<float> const& SoundData::getSamples() const { return m_samples; }

} // namespace oalpp
