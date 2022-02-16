#ifndef OPENALPP_SOUND_DATA_FAKE_HPP
#define OPENALPP_SOUND_DATA_FAKE_HPP

#include "oalpp/sound_data/sound_data_interface.hpp"

class SoundDataMonoFake : public oalpp::SoundDataInterface {
public:
    int getNumberOfChannels() const override;
    int getSampleRate() const override;
    std::vector<float> const& getSamples() const override;
    std::vector<float> m_samples {};
};

class SoundDataStereoFake : public oalpp::SoundDataInterface {
public:
    int getNumberOfChannels() const override;
    int getSampleRate() const override;
    std::vector<float> const& getSamples() const override;
    std::vector<float> m_samples {};
};

#endif // OPENALPP_SOUND_DATA_FAKE_HPP
