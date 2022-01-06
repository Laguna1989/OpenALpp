#ifndef OPENALTRYOUT_SOUND_DATA_HPP
#define OPENALTRYOUT_SOUND_DATA_HPP

#include "sound_data_interface.hpp"
#include <string>

class SoundData : public SoundDataInterface {
public:
    explicit SoundData(std::string const& fileName);

    virtual int getNumberOfChannels() const override;
    virtual int getSampleRate() const override;
    virtual std::vector<short> const& getSamples() const override;

private:
    std::vector<short> m_samples {};
    int m_sampleRate { 0 };
    int m_channels { 0 };
};

#endif // OPENALTRYOUT_SOUND_DATA_HPP
