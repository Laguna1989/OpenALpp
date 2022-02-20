#include "sound_data_with_effect.hpp"
#include <algorithm>

namespace oalpp {

SoundDataWithEffect::SoundDataWithEffect(
    SoundDataInterface const& decoratee, effects::MonoEffectInterface& effect)
{
    m_sampleRate = decoratee.getSampleRate();
    m_numberOfChannels = decoratee.getNumberOfChannels();
    if (m_numberOfChannels == 1) {
        m_samples = effect.process(decoratee.getSamples());
    } else {
        std::vector<float> lefts;
        std::vector<float> rights;
        unsigned int halfSize = decoratee.getSamples().size() / 2;
        lefts.resize(halfSize);
        rights.resize(halfSize);

        bool toggle = false;
        std::partition_copy(decoratee.getSamples().begin(), decoratee.getSamples().end(),
            lefts.begin(), rights.begin(), [&toggle](float) {
                toggle = !toggle;
                return toggle;
            });

        std::vector<float> const leftsProcessed = effect.process(lefts);
        std::vector<float> const rightsProcessed = effect.process(rights);

        m_samples.resize(leftsProcessed.size() * 2U);
        for (auto i = 0U; i != leftsProcessed.size(); ++i) {
            m_samples[i * 2U + 0U] = leftsProcessed[i];
            m_samples[i * 2U + 1U] = rightsProcessed[i];
        }
    }
}

int SoundDataWithEffect::getNumberOfChannels() const { return m_numberOfChannels; }
int SoundDataWithEffect::getSampleRate() const { return m_sampleRate; }
const std::vector<float>& SoundDataWithEffect::getSamples() const { return m_samples; }

} // namespace oalpp
