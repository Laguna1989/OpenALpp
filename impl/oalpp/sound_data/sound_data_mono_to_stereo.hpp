#ifndef OPENALPP_SOUND_DATA_MONO_TO_STEREO_HPP
#define OPENALPP_SOUND_DATA_MONO_TO_STEREO_HPP

#include "sound_data_interface.hpp"

namespace oalpp {

class SoundDataMonoToStereo : public SoundDataInterface {
public:
    explicit SoundDataMonoToStereo(SoundDataInterface& source);

    int getNumberOfChannels() const override;
    int getSampleRate() const override;
    std::vector<float> const& getSamples() const override;

private:
    std::vector<float> m_samples {};
    int m_sampleRate { 0 };
};

} // namespace oalpp

#endif // OPENALPP_SOUND_DATA_MONO_TO_STEREO_HPP
