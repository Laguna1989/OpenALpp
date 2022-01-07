#include "sound.hpp"
#include "sound_context.hpp"
#include <cmath>
#include <stdexcept>

Sound::Sound(SoundDataInterface const& soundData, SoundContext const& /*unused*/)
{
    ALenum format = AL_FORMAT_MONO16;
    if (soundData.getNumberOfChannels() == 2) {
        format = AL_FORMAT_STEREO16;
    }

    alGenBuffers(1, &m_bufferId);

    int size = soundData.getSamples().size();
    alBufferData(
        m_bufferId, format, soundData.getSamples().data(), size, soundData.getSampleRate());

    // Create source
    alGenSources(1, &m_sourceId);
    alSourcef(m_sourceId, AL_PITCH, 1.0f);
    alSourcef(m_sourceId, AL_GAIN, 1.0f);

    alSource3f(m_sourceId, AL_POSITION, 0.0f, 0.0f, -1.0f);
    alSource3f(m_sourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(m_sourceId, AL_LOOPING, AL_FALSE);

    alSourcef(m_sourceId, AL_ROLLOFF_FACTOR, 0.0f);
    alSourcei(m_sourceId, AL_SOURCE_RELATIVE, true);

    alSourcei(m_sourceId, AL_BUFFER, m_bufferId);

    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        auto const errorMessage
            = "Could not create OpenAL soundData, error code: " + std::to_string(errorIfAny);
        throw std::logic_error { errorMessage.c_str() };
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
        throw std::logic_error { errorMessage.c_str() };
    }
}

bool Sound::isPlaying() const
{
    ALint state = AL_PLAYING;
    alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}
float Sound::getVolume() const
{
    float value { 0.0f };
    alGetSourcef(m_sourceId, AL_GAIN, &value);
    return value;
}

void Sound::setVolume(float newVolume)
{
    if (newVolume < 0 || newVolume > 1.0f) {
        auto const errorMessage
            = std::string { "invalid volume value: " } + std::to_string(newVolume);
        throw std::invalid_argument { errorMessage.c_str() };
    }
    alSourcef(m_sourceId, AL_GAIN, newVolume);
}

float Sound::getPan() const
{
    float x { 0.0f };
    float y { 0.0f };
    float z { 0.0f };

    alGetSource3f(m_sourceId, AL_POSITION, &x, &y, &z);
    return x;
}

void Sound::setPan(float newPan)
{
    if (newPan < -1.0f || newPan > 1.0f) {
        auto const errorMessage = std::string { "invalid pan value: " } + std::to_string(newPan);
        throw std::invalid_argument { errorMessage.c_str() };
    }

    int channels { 0 };
    alGetBufferi(m_bufferId, AL_CHANNELS, &channels);
    if (channels != 1) {
        throw std::logic_error { std::string { "cannot set pan on non-mono file." }.c_str() };
    }

    alSource3f(m_sourceId, AL_POSITION, newPan, 0, -sqrt(1.0f - newPan * newPan));
}
