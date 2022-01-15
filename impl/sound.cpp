#include "sound.hpp"
#include "audio_exceptions.hpp"
#include "sound_context.hpp"
#include <cmath>
#include <stdexcept>

namespace oalpp {

Sound::Sound(SoundDataInterface const& soundData, SoundContext const& /*unused*/)
    : m_soundData { soundData }
{
    if (soundData.getNumberOfChannels() == 2) {
        m_format = AL_FORMAT_STEREO_FLOAT32;
    }

    // Create source
    alGenSources(1, &m_sourceId);
    alSourcef(m_sourceId, AL_PITCH, 1.0f);
    alSourcef(m_sourceId, AL_GAIN, m_volume);
    alSource3f(m_sourceId, AL_POSITION, 0.0f, 0, -1.0f);
    alSource3f(m_sourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(m_sourceId, AL_LOOPING, AL_FALSE);
    alSourcef(m_sourceId, AL_ROLLOFF_FACTOR, 0.0f);
    alSourcei(m_sourceId, AL_SOURCE_RELATIVE, true);

    // Create and fill buffers
    alGenBuffers(m_bufferIds.size(), m_bufferIds.data());

    for (std::size_t i = 0u; i != m_bufferIds.size(); ++i) {
        if (m_cursor >= m_soundData.getSamples().size()) {
            continue;
        }
        // TODO small audio files (less samples than buffer size) might cause issues here.
        queueBuffer(m_bufferIds.at(i), BUFFER_SIZE);
    }

    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        auto const errorMessage
            = "Could not create OpenAL soundData, error code: " + std::to_string(errorIfAny);
        throw oalpp::AudioException { errorMessage.c_str() };
    }
}

Sound::~Sound()
{
    alDeleteSources(1, &m_sourceId);
    alDeleteBuffers(m_bufferIds.size(), m_bufferIds.data());
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

    setPosition(
        std::array<float, 3> { newPan, 0, -static_cast<float>(sqrt(1.0f - newPan * newPan)) });
}

std::array<float, 3> Sound::getPosition() const { return m_position; }

void Sound::setPosition(std::array<float, 3> const& newPos)
{
    if (m_format == AL_FORMAT_STEREO_FLOAT32) {
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

void Sound::queueBuffer(ALuint buffer, std::size_t samplesToQueue)
{
    alBufferData(buffer, m_format, &m_soundData.getSamples()[m_cursor],
        samplesToQueue * sizeof(float), m_soundData.getSampleRate());
    alSourceQueueBuffers(m_sourceId, 1, &buffer);

    m_cursor += samplesToQueue;
}

void Sound::update()
{
    ALint buffersProcessed = 0;
    alGetSourcei(m_sourceId, AL_BUFFERS_PROCESSED, &buffersProcessed);

    if (buffersProcessed <= 0) {
        return;
    }

    while (buffersProcessed--) {
        if (m_cursor >= m_soundData.getSamples().size()) {
            continue;
        }

        ALuint buffer;
        alSourceUnqueueBuffers(m_sourceId, 1, &buffer);

        if (m_cursor + BUFFER_SIZE <= m_soundData.getSamples().size()) {
            // queue a full buffer
            queueBuffer(buffer, BUFFER_SIZE);
        } else {
            // queue only the remaining part of the file into the buffer
            std::size_t const remainingSamplesInSoundData
                = m_soundData.getSamples().size() - m_cursor;

            queueBuffer(buffer, remainingSamplesInSoundData);

            if (m_isLooping) {
                // reset cursor
                m_cursor = 0;
            }
        }
    }
}
bool Sound::getIsLooping() const { return m_isLooping; }
void Sound::setIsLooping(bool value) { m_isLooping = value; }

} // namespace oalpp
