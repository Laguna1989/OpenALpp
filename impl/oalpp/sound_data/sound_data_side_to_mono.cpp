#include "sound_data_side_to_mono.hpp"
#include <stdexcept>

namespace oalpp {

SoundDataSideToMono::SoundDataSideToMono(SoundDataInterface& source)
{
    if (source.getNumberOfChannels() != 2) {
        throw std::invalid_argument { "Can not convert left to mono from mono file." };
    }

    m_samples.resize(source.getSamples().size() / 2);

    for (auto index = 0U; index != m_samples.size(); ++index) {
        auto const left = source.getSamples().at(index * 2);
        auto const right = source.getSamples().at(index * 2 + 1);

        m_samples.at(index) = (left - right) / 2.0f;
    }
    m_sampleRate = source.getSampleRate();
}

int SoundDataSideToMono::getNumberOfChannels() const { return 1; }
int SoundDataSideToMono::getSampleRate() const { return m_sampleRate; }
std::vector<float> const& SoundDataSideToMono::getSamples() const { return m_samples; }

} // namespace oalpp
