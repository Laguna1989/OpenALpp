#ifndef OPENALPP_AL_HPP
#define OPENALPP_AL_HPP

#include "AL/al.h"
#ifdef __EMSCRIPTEN__
#ifndef AL_EXT_float32 // we assume AL_EXT_float32 is implemented
#define AL_EXT_float32 1
#define AL_FORMAT_MONO_FLOAT32 0x10010
#define AL_FORMAT_STEREO_FLOAT32 0x10011
#endif // AL_EXT_float32
#else
#include "AL/alext.h"
#endif // __EMSCRIPTEN__

#endif // OPENALPP_AL_HPP
