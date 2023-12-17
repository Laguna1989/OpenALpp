#include "sound_data_left_to_mono.hpp"
#include <stdexcept>

namespace oalpp {

SoundDataLeftToMono::SoundDataLeftToMono(SoundDataInterface& source)
{
    if (source.getNumberOfChannels() != 2) {
        throw std::invalid_argument { "Can not convert left to mono from mono file." };
    }

    m_samples.resize(source.getSamples().size() / 2);

    for (auto index = 0U; index != m_samples.size(); ++index) {
        m_samples.at(index) = source.getSamples().at(index * 2);
    }
    m_sampleRate = source.getSampleRate();
}

int SoundDataLeftToMono::getNumberOfChannels() const { return 1; }

int SoundDataLeftToMono::getSampleRate() const { return m_sampleRate; }

std::vector<float> const& SoundDataLeftToMono::getSamples() const { return m_samples; }

} // namespace oalpp
