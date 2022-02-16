#ifndef OPENALPP_SOUNDCONTEXTINTERFACE_HPP
#define OPENALPP_SOUNDCONTEXTINTERFACE_HPP

namespace oalpp {
class SoundContextInterface {
public:
    virtual ~SoundContextInterface() = default;

    // avoid slicing via polymorphic copy or move
    SoundContextInterface(SoundContextInterface const& /*other*/) = delete;
    SoundContextInterface(SoundContextInterface&& /*other*/) = delete;
    SoundContextInterface& operator=(const SoundContextInterface&) = delete;
    SoundContextInterface& operator=(SoundContextInterface&&) = delete;

protected:
    // allow default construction for derived classes
    SoundContextInterface() = default;
};
} // namespace oalpp

#endif // OPENALPP_SOUNDCONTEXTINTERFACE_HPP
