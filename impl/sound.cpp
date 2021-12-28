#include "sound.hpp"
#include "low_level_frickel.hpp"
#include "stb_vorbis.hpp"

Sound::Sound(const std::string& fileName)
{
    int chan { 0 };
    int sampleRate { 0 };
    int numberOfSamples = stb_vorbis_decode_filename(fileName.c_str(), &chan, &sampleRate, &output);

    alCall(alGenBuffers, 1, &buffer);
    ALenum format = AL_FORMAT_MONO16;

    alCall(alBufferData, buffer, format, output, numberOfSamples, sampleRate);

    // Create source
    alCall(alGenSources, 1, &source);
    alCall(alSourcef, source, AL_PITCH, 1);
    alCall(alSourcef, source, AL_GAIN, 1.0f);
    alCall(alSource3f, source, AL_POSITION, 0, 0, 0);
    alCall(alSource3f, source, AL_VELOCITY, 0, 0, 0);
    alCall(alSourcei, source, AL_LOOPING, AL_FALSE);
    alCall(alSourcei, source, AL_BUFFER, buffer);
}

void Sound::play()
{
    alCall(alSourcePlay, source);

    ALint state = AL_PLAYING;

    while (state == AL_PLAYING) {
        alCall(alGetSourcei, source, AL_SOURCE_STATE, &state);
    }
}
