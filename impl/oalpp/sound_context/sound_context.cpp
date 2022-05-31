#include "sound_context.hpp"
#include "oalpp/common/audio_exceptions.hpp"

namespace oalpp {

namespace {
auto defaultDeviceFactory()
{
    return std::unique_ptr<ALCdevice, SoundContext::DeviceDestroyer>(
        alcOpenDevice(nullptr), alcCloseDevice);
}

} // namespace

SoundContext::SoundContext(
    std::function<std::unique_ptr<ALCdevice, DeviceDestroyer>()> deviceFactory)
{
    if (numberOfInitializations != 0) {
        throw oalpp::AudioSystemException { "Sound context has to be unique" };
    }
    numberOfInitializations++;

    if (deviceFactory == nullptr) {
        deviceFactory = defaultDeviceFactory;
    }
    m_device = deviceFactory();

    if (!m_device) {
        numberOfInitializations--;
        throw oalpp::AudioSystemException { "Could not open audio device" };
    }

    m_context = std::unique_ptr<ALCcontext, ContextDestroyer>(
        alcCreateContext(m_device.get(), nullptr), [](ALCcontext* context) {
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(context);
        });
    if (!m_context) {
        numberOfInitializations--;
        throw oalpp::AudioSystemException { "Could not create audio context" };
    }

    auto const contextMadeCurrent = alcMakeContextCurrent(m_context.get());
    if (!contextMadeCurrent) {
        numberOfInitializations--;
        throw oalpp::AudioSystemException { "Could not make audio context current" };
    }
}

SoundContext::~SoundContext() { numberOfInitializations--; }

int SoundContext::numberOfInitializations { 0 };

} // namespace oalpp
