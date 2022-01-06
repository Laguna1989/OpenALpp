#include "sound.hpp"
#include "sound_context.hpp"

Sound::Sound(SoundDataInterface const& buffer, SoundContext const& ctx)
{
    ALenum format = AL_FORMAT_MONO16;
    if (buffer.getNumberOfChannels() == 2) {
        format = AL_FORMAT_STEREO16;
    }

    alGenBuffers(1, &m_bufferId);

    int size = buffer.getSamples().size();
    alBufferData(m_bufferId, format, buffer.getSamples().data(), size, buffer.getSampleRate());
    {
        auto const errorIfAny = alGetError();
        if (errorIfAny != AL_NO_ERROR) {
            auto const errorMessage
                = "Could not create OpenAL buffer, error code: " + std::to_string(errorIfAny);
            throw std::exception { errorMessage.c_str() };
        }
    }

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
