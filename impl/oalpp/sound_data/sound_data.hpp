#ifndef OPENALPP_SOUND_DATA_HPP
#define OPENALPP_SOUND_DATA_HPP

#include <oalpp/sound_data/sound_data_interface.hpp>

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

    int getNumberOfChannels() const noexcept override;
    int getSampleRate() const noexcept override;
    std::vector<float> const& getSamples() const noexcept override;

private:
    std::vector<float> m_samples {};
    int m_sampleRate { 0 };
    int m_numberOfChannels { 0 };
};

} // namespace oalpp

#endif // OPENALPP_SOUND_DATA_HPP
