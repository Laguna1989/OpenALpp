#include "sound.hpp"
#include "stb_vorbis.hpp"
#include <iostream>

Sound::Sound(const std::string& fileName)
{
    int chan { 0 };
    int sampleRate { 0 };
    short* rawData { nullptr };
    int numberOfSamples
        = stb_vorbis_decode_filename(fileName.c_str(), &chan, &sampleRate, &rawData);

    std::cout << "numberOfSamples " << numberOfSamples << std::endl;

    m_buffer.resize(numberOfSamples);
    memcpy(m_buffer.data(), rawData, numberOfSamples);
    free(rawData);

    alGenBuffers(1, &m_bufferId);

    ALenum format = AL_FORMAT_MONO16;

    alBufferData(m_bufferId, format, m_buffer.data(), numberOfSamples, sampleRate);

    // Create source
    alGenSources(1, &m_sourceId);
    alSourcef(m_sourceId, AL_PITCH, 1.0);
    alSourcef(m_sourceId, AL_GAIN, 1.0f);
    alSource3f(m_sourceId, AL_POSITION, 0, 0, 0);
    alSource3f(m_sourceId, AL_VELOCITY, 0, 0, 0);
    alSourcei(m_sourceId, AL_LOOPING, AL_FALSE);
    alSourcei(m_sourceId, AL_BUFFER, m_bufferId);
}

void Sound::play()
{
    alSourcePlay(m_sourceId);

    ALint state = AL_PLAYING;

    while (state == AL_PLAYING) {
        alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);
    }
    alSourceStop(m_sourceId);
}
