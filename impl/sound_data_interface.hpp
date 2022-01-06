#ifndef OPENALTRYOUT_SOUND_DATA_INTERFACE_HPP
#define OPENALTRYOUT_SOUND_DATA_INTERFACE_HPP

#include <cstddef>
#include <vector>

class SoundDataInterface {
public:
    virtual ~SoundDataInterface() = default;
    virtual int getNumberOfChannels() const = 0;
    virtual int getSampleRate() const = 0;
    virtual std::vector<short> const& getSamples() const = 0;
};

#endif // OPENALTRYOUT_SOUND_DATA_INTERFACE_HPP
