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
    virtual std::vector<char> const& getSamples() const = 0;
};

} // namespace oalpp

#endif // OPENALPP_SOUND_DATA_INTERFACE_HPP
