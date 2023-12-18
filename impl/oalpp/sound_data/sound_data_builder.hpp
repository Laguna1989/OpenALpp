#ifndef SOUND_DATA_BUILDER_HPP
#define SOUND_DATA_BUILDER_HPP

#include "oalpp/effects/utility/gain.hpp"
#include <oalpp/sound_data/sound_data.hpp>
#include <string>
#include <vector>

namespace oalpp {

class SoundDataBuilder {
public:
    /// create SoundData from the builder
    /// \return SoundData object
    [[nodiscard]] SoundData create();

    /// Load SoundData content from file. This will overwrite any previously stored SoundData
    /// \param file path to the file
    /// \return SoundDataBuilder object (fluent interface)
    [[nodiscard]] SoundDataBuilder& fromFile(std::string const& file);

    /// Apply an effect to the SoundData
    /// \param effect effect to be applied
    /// \return SoundDataBuilder object (fluent interface)
    [[nodiscard]] SoundDataBuilder& withEffect(oalpp::effects::MonoEffectInterface& effect);

    /// Use only the left channel of the SoundData. If this is called on any non-stereo SoundData,
    /// an exception is raised.
    /// \return SoundDataBuilder object (fluent interface)
    [[nodiscard]] SoundDataBuilder& onlyLeftChannel();

    /// Use only the right channel of the SoundData. If this is called on any non-stereo SoundData,
    /// an exception is raised.
    /// \return SoundDataBuilder object (fluent interface)
    [[nodiscard]] SoundDataBuilder& onlyRightChannel();

    /// Convert a mono SoundData to a stereo SoundData. If this is called on any non-mono
    /// SoundData, an exception is raised.
    /// \return SoundDataBuilder object (fluent interface)
    [[nodiscard]] SoundDataBuilder& toStereo();

private:
    std::vector<float> m_data {};
    int m_sampleRate { 0 };
    int m_numberOfChannels { 0 };
};

} // namespace oalpp

#endif // SOUND_DATA_BUILDER_HPP
