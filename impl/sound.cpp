#include "sound.hpp"
#include "libnyquist/Decoders.h"
#include <iostream>

Sound::Sound(const std::string& fileName)
{
    auto fileData = std::make_shared<nqr::AudioData>();
    nqr::NyquistIO loader;
    loader.Load(fileData.get(), fileName);

    std::size_t size = fileData->samples.size();
    ALenum format = AL_FORMAT_MONO16;
    if (fileData->channelCount == 2) {
        format = AL_FORMAT_STEREO16;
        if (fileData->samples.size() % 4 != 0) {
            size += 2;
        }
    }

    m_buffer.resize(size);

    std::transform(fileData->samples.begin(), fileData->samples.end(), m_buffer.begin(),
        [](auto in) { return static_cast<short>(in * std::numeric_limits<short>::max()); });

    alGenBuffers(1, &m_bufferId);

    alBufferData(m_bufferId, format, m_buffer.data(), m_buffer.size(), fileData->sampleRate);

    // Create source
    alGenSources(1, &m_sourceId);
    alSourcef(m_sourceId, AL_PITCH, 1.0f);
    alSourcef(m_sourceId, AL_GAIN, 0.25f);
    alSource3f(m_sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(m_sourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(m_sourceId, AL_LOOPING, AL_FALSE);
    alSourcei(m_sourceId, AL_BUFFER, m_bufferId);

    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        auto const errorMessage
            = "Could not create OpenAL buffer, error code: " + std::to_string(errorIfAny);
        throw std::exception { errorMessage.c_str() };
    }
}

Sound::~Sound()
{
    alDeleteSources(1, &m_sourceId);
    alDeleteBuffers(1, &m_bufferId);
}

void Sound::play()
{
    alSourcePlay(m_sourceId);
    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        auto const errorMessage = "Could not play sound, error code: " + std::to_string(errorIfAny);
        throw std::exception { errorMessage.c_str() };
    }
}

bool Sound::isPlaying() const
{
    ALint state = AL_PLAYING;
    alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}
