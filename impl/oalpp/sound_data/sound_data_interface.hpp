#ifndef OPENALPP_SOUND_DATA_INTERFACE_HPP
#define OPENALPP_SOUND_DATA_INTERFACE_HPP

#include <cstddef>
#include <vector>

namespace oalpp {

class SoundDataInterface {
public:
    /// Get number of channels. This will return 1 for mono and 2 for stereo SoundData
    /// \return number of channels
    virtual int getNumberOfChannels() const = 0;

    /// Get sample rate
    /// \return sample rate in Hz
    virtual int getSampleRate() const = 0;

    /// access samples
    /// \return reference to const data
    virtual std::vector<float> const& getSamples() const = 0;


    // virtual destructor, avoid leaking data
    virtual ~SoundDataInterface() = default;

    // avoid slicing via polymorphic copy or move
    SoundDataInterface(SoundDataInterface const& /*other*/) = delete;
    SoundDataInterface(SoundDataInterface&& /*other*/) = delete;
    SoundDataInterface& operator=(SoundDataInterface const&) = delete;
    SoundDataInterface& operator=(SoundDataInterface&&) = delete;

protected:
    // allow default construction only for derived classes
    SoundDataInterface() = default;
};

} // namespace oalpp

#endif // OPENALPP_SOUND_DATA_INTERFACE_HPP
