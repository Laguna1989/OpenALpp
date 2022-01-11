#ifndef OPENALPP_SOUND_DATA_INTERFACE_HPP
#define OPENALPP_SOUND_DATA_INTERFACE_HPP

#include <cstddef>
#include <vector>

class SoundDataInterface {
public:
    virtual ~SoundDataInterface() = default;
    virtual int getNumberOfChannels() const = 0;
    virtual int getSampleRate() const = 0;
    virtual std::vector<short> const& getSamples() const = 0;
};

#endif // OPENALPP_SOUND_DATA_INTERFACE_HPP
