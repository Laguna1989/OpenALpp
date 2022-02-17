#include "sound_data_with_effect.hpp"
#include <algorithm>

namespace oalpp {
SoundDataWithEffect::SoundDataWithEffect(
    SoundDataInterface const& decoratee, effects::MonoEffectIterative& effect)
{
    m_sampleRate = decoratee.getSampleRate();
    m_numberOfChannels = decoratee.getNumberOfChannels();
    m_samples.resize(decoratee.getSamples().size());

    auto const& samples = decoratee.getSamples();
    if (m_numberOfChannels == 1) {
        applyEffectToMonoSoundData(effect, samples);
    } else {
        applyEffectToStereoSoundData(effect, samples);
    }
}

SoundDataWithEffect::SoundDataWithEffect(
    SoundDataInterface const& decoratee, effects::MonoEffectBulk& effect)
{
    m_sampleRate = decoratee.getSampleRate();
    m_numberOfChannels = decoratee.getNumberOfChannels();
    if (m_numberOfChannels == 1) {
        m_samples = effect.process(decoratee.getSamples());
    } else {
        std::vector<float> lefts;
        std::vector<float> rights;
        lefts.resize(decoratee.getSamples().size() / 2);
        rights.resize(decoratee.getSamples().size() / 2);
        bool toggle = false;

        std::partition_copy(decoratee.getSamples().begin(), decoratee.getSamples().end(),
            lefts.begin(), rights.begin(), [&toggle](float) { return toggle = !toggle; });

        std::vector<float> const leftsProcessed = effect.process(lefts);
        std::vector<float> const rightsProcessed = effect.process(rights);

        m_samples.resize(decoratee.getSamples().size() * 2);
        for (auto i = 0; i != leftsProcessed.size(); ++i) {
            m_samples[i * 2 + 0] = leftsProcessed[i];
            m_samples[i * 2 + 1] = rightsProcessed[i];
        }
    }
}

void SoundDataWithEffect::applyEffectToStereoSoundData(
    effects::MonoEffectIterative& effect, std::vector<float> const& samples)
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
    effects::MonoEffectIterative& effect, std::vector<float> const& samples)
{
    std::transform(samples.cbegin(), samples.cend(), m_samples.begin(),
        [&effect](auto f) { return effect.process(f); });
}

int SoundDataWithEffect::getNumberOfChannels() const { return m_numberOfChannels; }
int SoundDataWithEffect::getSampleRate() const { return m_sampleRate; }
const std::vector<float>& SoundDataWithEffect::getSamples() const { return m_samples; }

} // namespace oalpp
