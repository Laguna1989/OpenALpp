#include "sound_data.hpp"
#include "libnyquist/Decoders.h"

SoundData::SoundData(std::string const& fileName)
{
    auto fileData = std::make_shared<nqr::AudioData>();
    nqr::NyquistIO loader;
    loader.Load(fileData.get(), fileName);

    m_channels = fileData->channelCount;
    m_sampleRate = fileData->sampleRate;

    std::size_t size = fileData->samples.size();
    if (fileData->channelCount == 2) {
        if (fileData->samples.size() % 4 != 0) {
            // TODO figure out why there seems to be one sample missing when exporting with reaper.
            size += 2;
        }
    }

    m_samples.resize(size);

    std::transform(fileData->samples.begin(), fileData->samples.end(), m_samples.begin(),
        [](auto in) { return static_cast<short>(in * std::numeric_limits<short>::max()); });
}

int SoundData::getNumberOfChannels() const { return m_channels; }

int SoundData::getSampleRate() const { return m_sampleRate; }

std::vector<short> const& SoundData::getSamples() const { return m_samples; }
