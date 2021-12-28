#ifndef OPENALTRYOUT_SOUND_CONTEXT_HPP
#define OPENALTRYOUT_SOUND_CONTEXT_HPP

#include "alc.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class SoundContext {
public:
    SoundContext();
    ~SoundContext();

private:
    // TODO make smart pointer
    // TODO naming scheme
    ALCdevice* openALDevice { nullptr };
    ALCcontext* openALContext { nullptr };
    ALCboolean contextMadeCurrent { false };
};

#endif // OPENALTRYOUT_SOUND_CONTEXT_HPP
