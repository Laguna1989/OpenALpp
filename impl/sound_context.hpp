#ifndef OPENALTRYOUT_SOUND_CONTEXT_HPP
#define OPENALTRYOUT_SOUND_CONTEXT_HPP

#include "AL/al.h"
#include "AL/alc.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class SoundContext {
public:
    SoundContext();
    ~SoundContext();

    void play();

private:
    // TODO make smart pointer
    // TODO naming scheme
    ALCdevice* openALDevice { nullptr };
    ALCcontext* openALContext { nullptr };
    ALCboolean contextMadeCurrent { false };

    // TODO move to sound class
    ALuint buffer;
    short* output;
    ALuint source;
};

#endif // OPENALTRYOUT_SOUND_CONTEXT_HPP
