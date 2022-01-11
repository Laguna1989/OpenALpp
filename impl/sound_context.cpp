#include "sound_context.hpp"
#include "audio_exceptions.hpp"

SoundContext::SoundContext()
{
    if (numberOfInitializations != 0) {
        throw oalpp::AudioSystemException { "Sound context has to be unique" };
    }
    numberOfInitializations++;

    m_device = alcOpenDevice(nullptr);
    if (!m_device) {
        throw oalpp::AudioSystemException { "Could not open audio device" };
    }

    m_context = alcCreateContext(m_device, nullptr);
    if (!m_context) {
        throw oalpp::AudioSystemException { "Could not create audio context" };
    }

    auto const contextMadeCurrent = alcMakeContextCurrent(m_context);
    if (!contextMadeCurrent) {
        throw oalpp::AudioSystemException { "Could not make audio context current" };
    }
}

SoundContext::~SoundContext()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);

    numberOfInitializations--;
}

int SoundContext::numberOfInitializations { 0 };
