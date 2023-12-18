#ifndef SOUND_DATA_BUILDER_HPP
#define SOUND_DATA_BUILDER_HPP

#include "oalpp/effects/utility/gain.hpp"
#include <oalpp/sound_data/sound_data.hpp>
#include <string>
#include <vector>

namespace oalpp {

class SoundDataBuilder {
public:
    [[nodiscard]] SoundData create();

    [[nodiscard]] SoundDataBuilder& fromFile(std::string const& file);
    [[nodiscard]] SoundDataBuilder& toString(std::string& str);
    [[nodiscard]] SoundDataBuilder& withEffect(oalpp::effects::MonoEffectInterface& effect);
    [[nodiscard]] SoundDataBuilder& onlyLeftChannel();
    [[nodiscard]] SoundDataBuilder& onlyRightChannel();
    [[nodiscard]] SoundDataBuilder& toStereo();

private:
    std::vector<float> m_data {};
    int m_sampleRate { 0 };
    int m_numberOfChannels { 0 };
};

} // namespace oalpp

#endif // SOUND_DATA_BUILDER_HPP
