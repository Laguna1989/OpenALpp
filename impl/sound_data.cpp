#include "sound_data.hpp"
#include "libnyquist/Decoders.h"

namespace oalpp {

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

    // TODO why???
    m_samples.resize(size * 2);
    for (auto i = 0u; i != fileData->samples.size(); ++i) {
        float const in = fileData->samples.at(i);
        float in_scaled = in * std::numeric_limits<char>::max();
        short myshort = static_cast<short>(in_scaled);
        char Lo = myshort & (0xff);
        char Hi = myshort & (0xff00);
        Hi <<= 8;
        m_samples.at(i * 2) = Hi;
        m_samples.at(i * 2 + 1) = Lo;
    }
}

int SoundData::getNumberOfChannels() const { return m_channels; }

int SoundData::getSampleRate() const { return m_sampleRate; }

std::vector<char> const& SoundData::getSamples() const { return m_samples; }

} // namespace oalpp
