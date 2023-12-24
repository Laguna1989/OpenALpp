#include "sound_data.hpp"
#include <utility>

namespace oalpp {

SoundData::SoundData(std::vector<float> const& data, int sampleRate, int numberOfChannels)
    : m_samples { data }
    , m_sampleRate { sampleRate }
    , m_numberOfChannels { numberOfChannels }
{
}

SoundData::SoundData(SoundData&& data) noexcept
    : m_samples { std::move(data.m_samples) }
    , m_sampleRate { std::exchange(data.m_sampleRate, 0) }
    , m_numberOfChannels { std::exchange(data.m_numberOfChannels, 0) }
{
}

SoundData& SoundData::operator=(SoundData&& other) noexcept
{
    m_samples = std::move(other.m_samples);
    m_sampleRate = std::exchange(other.m_sampleRate, 0);
    m_numberOfChannels = std::exchange(other.m_numberOfChannels, 0);
    return *this;
}

int SoundData::getNumberOfChannels() const noexcept { return m_numberOfChannels; }

int SoundData::getSampleRate() const noexcept { return m_sampleRate; }

std::vector<float> const& SoundData::getSamples() const noexcept { return m_samples; }

} // namespace oalpp
