#include "sound_context.hpp"
#include "low_level_frickel.hpp"

SoundContext::SoundContext()
{
    m_device = alcOpenDevice(nullptr);
    if (!m_device) {
        throw std::exception { "could not open audio device" };
    }

    if (!alcCall(alcCreateContext, m_context, m_device, m_device, nullptr) || !m_context) {
        throw std::exception { "Could not create audio context" };
    }

    ALCboolean contextMadeCurrent { false };
    if (!alcCall(alcMakeContextCurrent, contextMadeCurrent, m_device, m_context)
        || contextMadeCurrent != ALC_TRUE) {
        throw std::exception { "Could not make audio context current" };
    }
}

SoundContext::~SoundContext()
{
    ALCboolean contextMadeCurrent { true };
    alcCall(alcMakeContextCurrent, contextMadeCurrent, m_device, nullptr);
    alcCall(alcDestroyContext, m_device, m_context);
    alcCloseDevice(m_device);
}
