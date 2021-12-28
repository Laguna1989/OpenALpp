#include "sound_context.hpp"
#include "low_level_frickel.hpp"

SoundContext::SoundContext()
{
    openALDevice = alcOpenDevice(nullptr);
    if (!openALDevice) {
        throw std::exception { "could not open audio device" };
    }

    if (!alcCall(alcCreateContext, openALContext, openALDevice, openALDevice, nullptr)
        || !openALContext) {
        std::cerr << "ERROR: Could not create audio context" << std::endl;
        /* probably exit program */
    }

    if (!alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, openALContext)
        || contextMadeCurrent != ALC_TRUE) {
        std::cerr << "ERROR: Could not make audio context current" << std::endl;
        /* probably exit or give up on having sound */
    }

    // Load ogg:
}

SoundContext::~SoundContext()
{
    alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
    alcCall(alcDestroyContext, openALDevice, openALContext);
    alcCloseDevice(openALDevice);
}
