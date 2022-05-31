#ifndef OPENALPP_SOUND_CONTEXT_HPP
#define OPENALPP_SOUND_CONTEXT_HPP

#include "oalpp/common/alc.hpp"
#include "sound_context_interface.hpp"
#include <functional>
#include <memory>
#include <type_traits>

namespace oalpp {

class SoundContext : public SoundContextInterface {
public:
    using DeviceDestroyer = std::add_pointer<ALCboolean(ALCdevice*)>::type;
    using ContextDestroyer = std::add_pointer<void(ALCcontext*)>::type;

    SoundContext(
        std::function<std::unique_ptr<ALCdevice, DeviceDestroyer>()> deviceFactory = nullptr);
    ~SoundContext() override;

private:
    std::unique_ptr<ALCdevice, DeviceDestroyer> m_device { nullptr, nullptr };
    std::unique_ptr<ALCcontext, ContextDestroyer> m_context { nullptr, nullptr };
    static int numberOfInitializations;
};

} // namespace oalpp

#endif // OPENALPP_SOUND_CONTEXT_HPP
