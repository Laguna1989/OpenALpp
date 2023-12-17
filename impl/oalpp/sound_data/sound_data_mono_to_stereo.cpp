#include "sound_data_mono_to_stereo.hpp"
#include <stdexcept>

namespace oalpp {

SoundDataMonoToStereo::SoundDataMonoToStereo(SoundDataInterface& source)
{
    if (source.getNumberOfChannels() != 1) {
        throw std::invalid_argument { "Can not convert mono to stereo from non mono file." };
    }
    m_samples.resize(source.getSamples().size() * 2);

    for (auto index = 0U; index != source.getSamples().size(); ++index) {
        m_samples.at(index * 2 + 0) = source.getSamples().at(index);
        m_samples.at(index * 2 + 1) = source.getSamples().at(index);
    }
    m_sampleRate = source.getSampleRate();
}

int SoundDataMonoToStereo::getNumberOfChannels() const { return 2; }

int SoundDataMonoToStereo::getSampleRate() const { return m_sampleRate; }

std::vector<float> const& SoundDataMonoToStereo::getSamples() const { return m_samples; }

} // namespace oalpp
