#include "sound_data_with_effect.hpp"
#include <algorithm>

namespace oalpp {
SoundDataWithEffect::SoundDataWithEffect(
    SoundDataInterface& decoratee, effects::MonoEffectInterface& effect)
{
    m_sampleRate = decoratee.getSampleRate();
    m_channels = decoratee.getNumberOfChannels();
    m_samples.resize(decoratee.getSamples().size());
    auto& samples = decoratee.getSamples();
    std::transform(samples.cbegin(), samples.cend(), m_samples.begin(),
        [&effect](auto f) { return effect.process(f); });
}

int SoundDataWithEffect::getNumberOfChannels() const { return m_channels; }
int SoundDataWithEffect::getSampleRate() const { return m_sampleRate; }
const std::vector<float>& SoundDataWithEffect::getSamples() const { return m_samples; }

} // namespace oalpp
