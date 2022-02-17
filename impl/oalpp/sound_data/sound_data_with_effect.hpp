#ifndef OPENALPP_SOUND_DATA_WITH_EFFECT_HPP
#define OPENALPP_SOUND_DATA_WITH_EFFECT_HPP

#include "oalpp/effects/mono_effect_bulk.hpp"
#include "oalpp/effects/mono_effect_iterative.hpp"
#include "sound_data_interface.hpp"
#include <vector>

namespace oalpp {

class SoundDataWithEffect : public SoundDataInterface {
public:
    SoundDataWithEffect(SoundDataInterface const& decoratee, effects::MonoEffectIterative& effect);

    SoundDataWithEffect(SoundDataInterface const& decoratee, effects::MonoEffectBulk& effect);

    int getSampleRate() const override;
    const std::vector<float>& getSamples() const override;
    int getNumberOfChannels() const override;

private:
    std::vector<float> m_samples {};
    int m_sampleRate { 0 };
    int m_numberOfChannels { 0 };
    void applyEffectToMonoSoundData(
        effects::MonoEffectIterative& effect, std::vector<float> const& samples);
    void applyEffectToStereoSoundData(
        effects::MonoEffectIterative& effect, std::vector<float> const& samples);
};

} // namespace oalpp

#endif // OPENALPP_SOUND_DATA_WITH_EFFECT_HPP
