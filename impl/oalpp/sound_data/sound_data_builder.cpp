#include "sound_data_builder.hpp"
#include <libnyquist/Decoders.h>

oalpp::SoundDataBuilder& oalpp::SoundDataBuilder::fromFile(std::string const& file)
{
    nqr::NyquistIO loader;
    auto const audioData = std::make_unique<nqr::AudioData>();
    loader.Load(audioData.get(), file);
    m_data = std::move(audioData->samples);
    m_sampleRate = audioData->sampleRate;
    m_numberOfChannels = audioData->channelCount;
    return *this;
}

oalpp::SoundData oalpp::SoundDataBuilder::create()
{
    return oalpp::SoundData { m_data, m_sampleRate, m_numberOfChannels };
}

// TODO does not need to be part of builder, extract into free function
#if false
oalpp::SoundDataBuilder& oalpp::SoundDataBuilder::toString(std::string& str)
{
    str = "# Sound Data\n";
    str += "# sampleRate: " + std::to_string(m_sampleRate) + "\n";
    str += "# numberOfChannels: " + std::to_string(m_numberOfChannels) + "\n";

    for (auto index = 0U; index != m_data.size(); ++index) {
        str += std::to_string(index) + " " + std::to_string(m_data[index]) + "\n";
    }
    str += "\n";

    return *this;
}

#endif

oalpp::SoundDataBuilder& oalpp::SoundDataBuilder::withEffect(
    oalpp::effects::MonoEffectInterface& effect)
{
    if (m_numberOfChannels == 1) {
        m_data = effect.process(m_data);
    } else {
        std::vector<float> lefts;
        std::vector<float> rights;
        auto const halfSize = m_data.size() / 2;
        lefts.resize(halfSize);
        rights.resize(halfSize);

        bool toggle = false;
        std::partition_copy(
            m_data.begin(), m_data.end(), lefts.begin(), rights.begin(), [&toggle](float) {
                toggle = !toggle;
                return toggle;
            });

        std::vector<float> const leftsProcessed = effect.process(lefts);
        std::vector<float> const rightsProcessed = effect.process(rights);

        m_data.resize(leftsProcessed.size() * 2U);
        for (auto i = 0U; i != leftsProcessed.size(); ++i) {
            m_data[i * 2U + 0U] = leftsProcessed[i];
            m_data[i * 2U + 1U] = rightsProcessed[i];
        }
    }

    return *this;
}

oalpp::SoundDataBuilder& oalpp::SoundDataBuilder::onlyLeftChannel()
{
    if (m_numberOfChannels != 2) {
        throw std::invalid_argument { "Can not use left channel from mono sound data." };
    }

    std::vector<float> samples;
    samples.resize(m_data.size() / 2);

    for (auto index = 0U; index != samples.size(); ++index) {
        samples.at(index) = m_data.at(index * 2);
    }

    m_numberOfChannels = 1;
    m_data = samples;
    return *this;
}

oalpp::SoundDataBuilder& oalpp::SoundDataBuilder::onlyRightChannel()
{
    if (m_numberOfChannels != 2) {
        throw std::invalid_argument { "Can not use right channel from mono sound data." };
    }

    std::vector<float> samples;
    samples.resize(m_data.size() / 2);

    for (auto index = 0U; index != samples.size(); ++index) {
        samples.at(index) = m_data.at(index * 2 + 1);
    }

    m_numberOfChannels = 1;
    m_data = samples;
    return *this;
}

oalpp::SoundDataBuilder& oalpp::SoundDataBuilder::toStereo()
{
    if (m_numberOfChannels != 1) {
        throw std::invalid_argument { "Can not make stereo sound data from non-mono file." };
    }

    std::vector<float> samples;
    samples.resize(m_data.size() * 2);

    for (auto index = 0U; index != m_data.size(); ++index) {
        samples.at(index * 2 + 0) = m_data.at(index);
        samples.at(index * 2 + 1) = m_data.at(index);
    }

    m_data = samples;
    m_numberOfChannels = 2;

    return *this;
}
