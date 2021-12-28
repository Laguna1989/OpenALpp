#include "sound.hpp"
#include "low_level_frickel.hpp"
#include "stb_vorbis.hpp"

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

    alCall(alGenBuffers, 1, &m_bufferId);
    ALenum format = AL_FORMAT_MONO16;

    alCall(alBufferData, m_bufferId, format, m_buffer.data(), numberOfSamples, sampleRate);

    // Create source
    alCall(alGenSources, 1, &m_sourceId);
    alCall(alSourcef, m_sourceId, AL_PITCH, 1.0);
    alCall(alSourcef, m_sourceId, AL_GAIN, 1.0f);
    alCall(alSource3f, m_sourceId, AL_POSITION, 0, 0, 0);
    alCall(alSource3f, m_sourceId, AL_VELOCITY, 0, 0, 0);
    alCall(alSourcei, m_sourceId, AL_LOOPING, AL_FALSE);
    alCall(alSourcei, m_sourceId, AL_BUFFER, m_bufferId);
}

void Sound::play()
{
    alCall(alSourcePlay, m_sourceId);

    ALint state = AL_PLAYING;

    while (state == AL_PLAYING) {
        alCall(alGetSourcei, m_sourceId, AL_SOURCE_STATE, &state);
    }
    alSourceStop(m_sourceId);
}
