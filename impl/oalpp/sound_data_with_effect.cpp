#include "sound_data_with_effect.hpp"
#include <algorithm>

namespace oalpp {
SoundDataWithEffect::SoundDataWithEffect(
    SoundDataInterface const& decoratee, effects::MonoEffectInterface& effect)
{
    m_sampleRate = decoratee.getSampleRate();
    m_channels = decoratee.getNumberOfChannels();
    m_samples.resize(decoratee.getSamples().size());

    auto const& samples = decoratee.getSamples();
    if (m_channels == 1) {
        applyEffectToMonoSoundData(effect, samples);
    } else {
        applyEffectToStereoSoundData(effect, samples);
    }
}

void SoundDataWithEffect::applyEffectToStereoSoundData(
    effects::MonoEffectInterface& effect, std::vector<float> const& samples)
{
    // left channel
    for (auto i = 0U; i != samples.size(); ++i) {
        if (i % 2 == 0)
            m_samples.at(i) = effect.process(samples.at(i));
    }
    effect.reset();
    // right channel
    for (auto i = 0U; i != samples.size(); ++i) {
        if (i % 2 == 1)
            m_samples.at(i) = effect.process(samples.at(i));
    }
}

void SoundDataWithEffect::applyEffectToMonoSoundData(
    effects::MonoEffectInterface& effect, std::vector<float> const& samples)
{
    std::transform(samples.cbegin(), samples.cend(), m_samples.begin(),
        [&effect](auto f) { return effect.process(f); });
}

int SoundDataWithEffect::getNumberOfChannels() const { return m_channels; }
int SoundDataWithEffect::getSampleRate() const { return m_sampleRate; }
const std::vector<float>& SoundDataWithEffect::getSamples() const { return m_samples; }

} // namespace oalpp
