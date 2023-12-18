#ifndef OPENALPP_SOUND_DATA_HPP
#define OPENALPP_SOUND_DATA_HPP

#include "sound_data_interface.hpp"

namespace oalpp {

class SoundData : public SoundDataInterface {
public:
    SoundData(std::vector<float> const& data, int sampleRate, int numberOfChannels);
    SoundData() = delete;
    ~SoundData() override = default;

    SoundData(SoundData const& data) = delete;
    SoundData(SoundData&& data) noexcept;

    SoundData& operator=(SoundData const&) = delete;
    SoundData& operator=(SoundData&&) noexcept;


    int getNumberOfChannels() const override;
    int getSampleRate() const override;
    std::vector<float> const& getSamples() const override;

private:
    std::vector<float> m_samples {};
    int m_sampleRate { 0 };
    int m_numberOfChannels { 0 };
};

} // namespace oalpp

#endif // OPENALPP_SOUND_DATA_HPP
