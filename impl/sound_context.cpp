#include "sound_context.hpp"
#include <stdexcept>

SoundContext::SoundContext()
{
    if (numberOfInitializations != 0) {
        throw std::logic_error { "" };
    }
    numberOfInitializations++;

    m_device = alcOpenDevice(nullptr);
    if (!m_device) {
        throw std::logic_error { "could not open audio device" };
    }

    m_context = alcCreateContext(m_device, nullptr);
    if (!m_context) {
        throw std::logic_error { "Could not create audio context" };
    }

    auto const contextMadeCurrent = alcMakeContextCurrent(m_context);
    if (!contextMadeCurrent) {
        throw std::logic_error { "Could not make audio context current" };
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
