#include "AL/al.h"
#include "AL/alc.h"
#include "stb_vorbis.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#define alCall(function, ...) alCallImpl(__FILE__, __LINE__, function, __VA_ARGS__)

bool check_al_errors(const std::string& filename, const std::uint_fast32_t line)
{
    ALenum error = alGetError();
    if (error == AL_NO_ERROR) {
        return true;
    }
    std::cerr << "***ERROR*** (" << filename << ": " << line << ")\n";
    switch (error) {
    case AL_INVALID_NAME: {
        std::cerr << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function";
        break;
    }
    case AL_INVALID_ENUM: {
        std::cerr << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function";
        break;
    }
    case AL_INVALID_VALUE: {
        std::cerr << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function";
        break;
    }
    case AL_INVALID_OPERATION: {
        std::cerr << "AL_INVALID_OPERATION: the requested operation is not valid";
        break;
    }
    case AL_OUT_OF_MEMORY: {
        std::cerr << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out "
                     "of memory";
        break;
    }
    default: {
        std::cerr << "UNKNOWN AL ERROR: " << error;
    }
    }
    std::cerr << std::endl;
    return false;
}

template <typename alFunction, typename... Params>
auto alCallImpl(
    const char* filename, const std::uint_fast32_t line, alFunction function, Params... params) ->
    typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>,
        decltype(function(params...))>
{
    auto const ret = function(std::forward<Params>(params)...);
    check_al_errors(filename, line);
    return ret;
}

template <typename alFunction, typename... Params>
auto alCallImpl(
    const char* filename, const std::uint_fast32_t line, alFunction function, Params... params) ->
    typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
{
    function(std::forward<Params>(params)...);
    return check_al_errors(filename, line);
}

#define alcCall(function, device, ...)                                                             \
    alcCallImpl(__FILE__, __LINE__, function, device, __VA_ARGS__)

bool check_alc_errors(const std::string& filename, const std::uint_fast32_t line, ALCdevice* device)
{
    ALCenum error = alcGetError(device);
    if (error != ALC_NO_ERROR) {
        std::cerr << "***ERROR*** (" << filename << ": " << line << ")\n";
        switch (error) {
        case ALC_INVALID_VALUE:
            std::cerr << "ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function";
            break;
        case ALC_INVALID_DEVICE:
            std::cerr << "ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function";
            break;
        case ALC_INVALID_CONTEXT:
            std::cerr << "ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function";
            break;
        case ALC_INVALID_ENUM:
            std::cerr << "ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function";
            break;
        case ALC_OUT_OF_MEMORY:
            std::cerr
                << "ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function";
            break;
        default:
            std::cerr << "UNKNOWN ALC ERROR: " << error;
        }
        std::cerr << std::endl;
        return false;
    }
    return true;
}

template <typename alcFunction, typename... Params>
auto alcCallImpl(const char* filename, const std::uint_fast32_t line, alcFunction function,
    ALCdevice* device, Params... params) ->
    typename std::enable_if_t<std::is_same_v<void, decltype(function(params...))>, bool>
{
    function(std::forward<Params>(params)...);
    return check_alc_errors(filename, line, device);
}

template <typename alcFunction, typename ReturnType, typename... Params>
auto alcCallImpl(const char* filename, const std::uint_fast32_t line, alcFunction function,
    ReturnType& returnValue, ALCdevice* device, Params... params) ->
    typename std::enable_if_t<!std::is_same_v<void, decltype(function(params...))>, bool>
{
    returnValue = function(std::forward<Params>(params)...);
    return check_alc_errors(filename, line, device);
}

int main()
{
    ALCdevice* openALDevice = alcOpenDevice(nullptr);
    if (!openALDevice) {
        throw std::exception { "could not open audio device" };
    }

    ALCcontext* openALContext { nullptr };
    if (!alcCall(alcCreateContext, openALContext, openALDevice, openALDevice, nullptr)
        || !openALContext) {
        std::cerr << "ERROR: Could not create audio context" << std::endl;
        /* probably exit program */
    }

    ALCboolean contextMadeCurrent = false;
    if (!alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, openALContext)
        || contextMadeCurrent != ALC_TRUE) {
        std::cerr << "ERROR: Could not make audio context current" << std::endl;
        /* probably exit or give up on having sound */
    }

    // Load ogg:
    std::string fileName = "test.ogg";

    int chan { 0 };
    int sampleRate { 0 };
    short* output;
    int numberOfSamples = stb_vorbis_decode_filename(fileName.c_str(), &chan, &sampleRate, &output);
    std::cout << numberOfSamples << " " << sampleRate << std::endl;

    ALuint buffer;
    alCall(alGenBuffers, 1, &buffer);
    ALenum format = AL_FORMAT_MONO16;

    std::size_t duration = numberOfSamples / sampleRate;

    alCall(alBufferData, buffer, format, output, numberOfSamples, sampleRate);

    // Create source
    ALuint source;
    alCall(alGenSources, 1, &source);
    alCall(alSourcef, source, AL_PITCH, 1);
    alCall(alSourcef, source, AL_GAIN, 1.0f);
    alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
    alCall(alSource3f, source, AL_VELOCITY, 0, 0, 0);
    alCall(alSourcei, source, AL_LOOPING, AL_FALSE);
    alCall(alSourcei, source, AL_BUFFER, buffer);

    alCall(alSourcePlay, source);

    ALint state = AL_PLAYING;

    while(state == AL_PLAYING)
    {
        alCall(alGetSourcei, source, AL_SOURCE_STATE, &state);
    }

    // Cleanup:
    alcCall(alcMakeContextCurrent, contextMadeCurrent, openALDevice, nullptr);
    alcCall(alcDestroyContext, openALDevice, openALContext);

    auto closed = static_cast<bool>(alcCloseDevice(openALDevice));
    std::cout << "closed: " << std::boolalpha << static_cast<bool>(closed) << std::endl;

    return 0;
}
