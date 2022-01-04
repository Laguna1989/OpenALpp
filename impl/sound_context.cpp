#include "sound_context.hpp"

SoundContext::SoundContext()
{
    m_device = alcOpenDevice(nullptr);
    if (!m_device) {
        throw std::exception { "could not open audio device" };
    }

    m_context = alcCreateContext(m_device, nullptr);
    if (!m_context) {
        throw std::exception { "Could not create audio context" };
    }

    auto const contextMadeCurrent = alcMakeContextCurrent(m_context);
    if (!contextMadeCurrent) {
        throw std::exception { "Could not make audio context current" };
    }
}

SoundContext::~SoundContext()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}
