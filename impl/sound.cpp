#include "sound.hpp"
#include "audio_exceptions.hpp"
#include "sound_context.hpp"
#include <cmath>
#include <stdexcept>

namespace oalpp {

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
    alSourcef(m_sourceId, AL_GAIN, m_volume);
    alSource3f(m_sourceId, AL_POSITION, 0.0f, 0, -1.0f);
    alSource3f(m_sourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(m_sourceId, AL_LOOPING, AL_FALSE);

    alSourcef(m_sourceId, AL_ROLLOFF_FACTOR, 0.0f);
    alSourcei(m_sourceId, AL_SOURCE_RELATIVE, true);

    alSourcei(m_sourceId, AL_BUFFER, m_bufferId);

    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        auto const errorMessage
            = "Could not create OpenAL soundData, error code: " + std::to_string(errorIfAny);
        // TODO put sound into same namespace
        throw oalpp::AudioException { errorMessage.c_str() };
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
        throw oalpp::AudioException { errorMessage.c_str() };
    }
}

bool Sound::isPlaying() const
{
    ALint state = AL_PLAYING;
    alGetSourcei(m_sourceId, AL_SOURCE_STATE, &state);
    return (state == AL_PLAYING);
}

float Sound::getVolume() const { return m_volume; }

void Sound::setVolume(float newVolume)
{
    if (newVolume < 0 || newVolume > 1.0f) {
        auto const errorMessage
            = std::string { "Could not set volume value: " } + std::to_string(newVolume);
        throw std::invalid_argument { errorMessage.c_str() };
    }
    m_volume = newVolume;
    alSourcef(m_sourceId, AL_GAIN, newVolume);
}

void Sound::setPan(float newPan)
{
    if (newPan < -1.0f || newPan > 1.0f) {
        auto const errorMessage
            = std::string { "Could not set pan value: " } + std::to_string(newPan);
        throw std::invalid_argument { errorMessage.c_str() };
    }

    setPosition(std::array<float, 3> { newPan, 0, -sqrt(1.0f - newPan * newPan) });
}

std::array<float, 3> Sound::getPosition() const { return m_position; }

void Sound::setPosition(std::array<float, 3> const& newPos)
{
    int channels { 0 };
    alGetBufferi(m_bufferId, AL_CHANNELS, &channels);
    if (channels != 1) {
        throw oalpp::AudioException { "Could not set position on non-mono file" };
    }

    m_position = newPos;
    alSource3f(m_sourceId, AL_POSITION, newPos[0], newPos[1], newPos[2]);
}

float Sound::getPitch() const { return m_pitch; }

void Sound::setPitch(float const newPitch)
{
    if (newPitch <= 0.0f) {
        auto const errorMessage
            = std::string { "Could not set pitch value: " } + std::to_string(newPitch);
        throw std::invalid_argument { errorMessage.c_str() };
    }
    m_pitch = newPitch;
    alSourcef(m_sourceId, AL_PITCH, newPitch);
}

} // namespace oalpp
