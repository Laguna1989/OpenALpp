#include "sound_context.hpp"
#include "audio_exceptions.hpp"

namespace oalpp {

SoundContext::SoundContext()
{
    if (numberOfInitializations != 0) {
        throw oalpp::AudioSystemException { "Sound context has to be unique" };
    }
    numberOfInitializations++;

    m_device = std::unique_ptr<ALCdevice, DeviceDestroyer>(alcOpenDevice(nullptr), alcCloseDevice);

    if (!m_device) {
        throw oalpp::AudioSystemException { "Could not open audio device" };
    }

    m_context = std::unique_ptr<ALCcontext, ContextDestroyer>(
        alcCreateContext(m_device.get(), nullptr), [](ALCcontext* context) {
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(context);
        });
    if (!m_context) {
        throw oalpp::AudioSystemException { "Could not create audio context" };
    }

    auto const contextMadeCurrent = alcMakeContextCurrent(m_context.get());
    if (!contextMadeCurrent) {
        throw oalpp::AudioSystemException { "Could not make audio context current" };
    }
}

SoundContext::~SoundContext() { numberOfInitializations--; }

int SoundContext::numberOfInitializations { 0 };

} // namespace oalpp
