#ifndef OPENALPP_SOUND_DATA_INTERFACE_HPP
#define OPENALPP_SOUND_DATA_INTERFACE_HPP

#include <cstddef>
#include <vector>

namespace oalpp {

class SoundDataInterface {
public:
    virtual ~SoundDataInterface() = default;

    virtual int getNumberOfChannels() const = 0;
    virtual int getSampleRate() const = 0;
    virtual std::vector<float> const& getSamples() const = 0;

    // avoid slicing via polymorphic copy or move
    SoundDataInterface(SoundDataInterface const& /*other*/) = delete;
    SoundDataInterface(SoundDataInterface&& /*other*/) = delete;
    SoundDataInterface& operator=(SoundDataInterface const&) = delete;
    SoundDataInterface& operator=(SoundDataInterface&&) = delete;

protected:
    // allow default construction for derived classes
    SoundDataInterface() = default;
};

} // namespace oalpp

#endif // OPENALPP_SOUND_DATA_INTERFACE_HPP
