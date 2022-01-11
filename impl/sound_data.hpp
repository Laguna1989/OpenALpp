#ifndef OPENALPP_SOUND_DATA_HPP
#define OPENALPP_SOUND_DATA_HPP

#include "sound_data_interface.hpp"
#include <string>

namespace oalpp {

class SoundData : public SoundDataInterface {
public:
    explicit SoundData(std::string const& fileName);

    int getNumberOfChannels() const override;
    int getSampleRate() const override;
    std::vector<short> const& getSamples() const override;

private:
    std::vector<short> m_samples {};
    int m_sampleRate { 0 };
    int m_channels { 0 };
};

} // namespace oalpp

#endif // OPENALPP_SOUND_DATA_HPP
