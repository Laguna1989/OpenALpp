#include "sound_context.hpp"
#include <oalpp/common/audio_exceptions.hpp>

namespace oalpp {

namespace {

auto defaultDeviceFactory()
{
    return std::unique_ptr<ALCdevice, SoundContext::DeviceDestroyer>(
        alcOpenDevice(nullptr), alcCloseDevice);
}

auto defaultContextFactory(ALCdevice* device)
{
    return std::unique_ptr<ALCcontext, SoundContext::ContextDestroyer>(
        alcCreateContext(device, nullptr), [](ALCcontext* context) {
            alcMakeContextCurrent(nullptr);
            alcDestroyContext(context);
        });
}

bool defaultMakeContextCurrent(ALCcontext* context) { return alcMakeContextCurrent(context); }

} // namespace

SoundContext::SoundContext(SoundContext::DeviceFactoryT deviceFactory,
    SoundContext::ContextFactoryT contextFactory, MakeContextCurrentT makeContextCurrent)
{
    if (numberOfInitializations != 0) {
        throw oalpp::AudioSystemException { "Sound context has to be unique" };
    }

    if (deviceFactory == nullptr) {
        deviceFactory = defaultDeviceFactory;
    }
    m_device = deviceFactory();

    if (!m_device) {
        throw oalpp::AudioSystemException { "Could not open audio device" };
    }

    if (contextFactory == nullptr) {
        contextFactory = defaultContextFactory;
    }
    m_context = contextFactory(m_device.get());

    if (!m_context) {
        throw oalpp::AudioSystemException { "Could not create audio context" };
    }

    if (makeContextCurrent == nullptr) {
        makeContextCurrent = defaultMakeContextCurrent;
    }
    auto const contextMadeCurrent = makeContextCurrent(m_context.get());
    if (!contextMadeCurrent) {
        throw oalpp::AudioSystemException { "Could not make audio context current" };
    }

    numberOfInitializations++;
}

SoundContext::~SoundContext() { numberOfInitializations--; }

int SoundContext::numberOfInitializations { 0 };

} // namespace oalpp
