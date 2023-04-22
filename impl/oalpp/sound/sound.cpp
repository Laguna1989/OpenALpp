#include "sound.hpp"
#include "oalpp/common/audio_exceptions.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <stdexcept>

namespace oalpp {

Sound::Sound(SoundDataInterface const& soundData)
    : m_soundData { soundData }
{
    if (soundData.getNumberOfChannels() == 2) {
        m_format = AL_FORMAT_STEREO_FLOAT32;
    }

    initSourceAndBuffers();

    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        throw oalpp::AudioException { "Could not create OpenAL soundData, error code: "
            + std::to_string(errorIfAny) };
    }
}
void Sound::initSourceAndBuffers()
{
    // Create source
    alGenSources(1, &m_sourceId);
    alSourcef(m_sourceId, AL_PITCH, 1.0f);
    alSourcef(m_sourceId, AL_GAIN, m_volume);
    alSource3f(m_sourceId, AL_POSITION, 0.0f, 0, -1.0f);
    alSource3f(m_sourceId, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei(m_sourceId, AL_LOOPING, AL_FALSE);
    alSourcef(m_sourceId, AL_ROLLOFF_FACTOR, 0.0f);
    alSourcei(m_sourceId, AL_SOURCE_RELATIVE, true);

    alGenBuffers(static_cast<ALsizei>(m_bufferIds.size()), m_bufferIds.data());
    m_unqueuedBufferIds = std::list<ALuint> { m_bufferIds.cbegin(), m_bufferIds.cend() };
    m_cursor = 0;
    for (auto const& bufferId : m_unqueuedBufferIds) {
        selectSamplesForBuffer(bufferId);
    }
}

Sound::~Sound() { deleteSourceAndBuffers(); }

void Sound::deleteSourceAndBuffers()
{
    alDeleteSources(1, &m_sourceId);
    alDeleteBuffers(static_cast<ALsizei>(m_bufferIds.size()), m_bufferIds.data());
}

void Sound::play()
{
    alSourcePlay(m_sourceId);
    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        throw oalpp::AudioException { "Could not play sound, error code: "
            + std::to_string(errorIfAny) };
    }
}

void Sound::stop()
{
    alSourceStop(m_sourceId);

    deleteSourceAndBuffers();

    initSourceAndBuffers();

    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        throw oalpp::AudioException { "Could not stop sound, error code: "
            + std::to_string(errorIfAny) };
    }
}

void Sound::pause()
{
    alSourcePause(m_sourceId);
    auto const errorIfAny = alGetError();
    if (errorIfAny != AL_NO_ERROR) {
        throw oalpp::AudioException { "Could not stop sound, error code: "
            + std::to_string(errorIfAny) };
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
        throw std::invalid_argument { "Could not set volume value: " + std::to_string(newVolume) };
    }
    m_volume = newVolume;
    alSourcef(m_sourceId, AL_GAIN, newVolume);
}

void Sound::setPan(float newPan)
{
    if (newPan < -1.0f || newPan > 1.0f) {
        throw std::invalid_argument {
            ("Could not set pan value: " + std::to_string(newPan)).c_str()
        };
    }

    setPosition(Position { newPan, 0, -static_cast<float>(sqrt(1.0f - newPan * newPan)) });
}

Position Sound::getPosition() const { return m_position; }

void Sound::setPosition(Position const& newPosition)
{
    if (m_format == AL_FORMAT_STEREO_FLOAT32) {
        throw oalpp::AudioException { "Could not set position on non-mono file" };
    }

    m_position = newPosition;
    alSource3f(m_sourceId, AL_POSITION, newPosition.x, newPosition.y, newPosition.z);
}

float Sound::getPitch() const { return m_pitch; }

void Sound::setPitch(float const newPitch)
{
    if (newPitch <= 0.0f) {
        throw std::invalid_argument { "Could not set pitch value: " + std::to_string(newPitch) };
    }
    m_pitch = newPitch;
    alSourcef(m_sourceId, AL_PITCH, newPitch);
}

void Sound::enqueueSamplesToBuffer(ALuint bufferId, std::size_t samplesToQueue)
{
    alBufferData(bufferId, m_format, &m_soundData.getSamples()[m_cursor],
        static_cast<ALsizei>(samplesToQueue) * sizeof(float), m_soundData.getSampleRate());
    alSourceQueueBuffers(m_sourceId, 1, &bufferId);

    markBufferAsUnqueued(bufferId);

    m_cursor += samplesToQueue;
}

void Sound::update()
{
    ALint buffersProcessed = getNumberOfBuffersProcessed();

    assert(buffersProcessed <= static_cast<int>(BUFFER_COUNT));
    assert(buffersProcessed >= 0);

    while (buffersProcessed--) {
        if (m_cursor >= m_soundData.getSamples().size()) {
            break;
        }

        ALuint bufferId;
        alSourceUnqueueBuffers(m_sourceId, 1, &bufferId);
        markBufferAsQueued(bufferId);
        selectSamplesForBuffer(bufferId);
    }
}

ALint Sound::getNumberOfBuffersProcessed() const
{
    ALint numberOfBuffersProcessed = 0;
    alGetSourcei(m_sourceId, AL_BUFFERS_PROCESSED, &numberOfBuffersProcessed);
    return numberOfBuffersProcessed;
}

std::list<ALuint> Sound::getUnqueuedBufferIds() const { return m_unqueuedBufferIds; }

void Sound::selectSamplesForBuffer(ALuint bufferId)
{
    if (!hasDataToEnqueue()) {
        // do not queue any buffer
        return;
    }

    if (hasDataForFullBufferToEnqueue()) {
        // queue a full buffer
        enqueueSamplesToBuffer(bufferId, BUFFER_SIZE);
    } else {
        // queue only the remaining part of the soundData into the buffer
        std::size_t const remainingSamplesInSoundData = m_soundData.getSamples().size() - m_cursor;

        enqueueSamplesToBuffer(bufferId, remainingSamplesInSoundData);

        if (m_isLooping) {
            // reset cursor
            m_cursor = 0;
        }
    }
}

bool Sound::hasDataForFullBufferToEnqueue() const
{
    return m_cursor + BUFFER_SIZE <= m_soundData.getSamples().size();
}
bool Sound::hasDataToEnqueue() const
{
    if (m_isLooping) {
        return m_cursor <= m_soundData.getSamples().size();
    } else {
        return m_cursor < m_soundData.getSamples().size();
    }
}

bool Sound::getIsLooping() const { return m_isLooping; }
void Sound::setIsLooping(bool value)
{
    m_isLooping = value;
    if (m_isLooping) {
        for (auto const& bufferId : getUnqueuedBufferIds()) {
            selectSamplesForBuffer(bufferId);
        }
    }
}

size_t Sound::getLengthInSamples() const
{
    return m_soundData.getSamples().size() / m_soundData.getNumberOfChannels();
}
float Sound::getLengthInSeconds() const
{
    return static_cast<float>(getLengthInSamples())
        / static_cast<float>(m_soundData.getSampleRate());
}

float Sound::getCurrentOffsetInSeconds() const
{
    return static_cast<float>(getCurrentOffsetInSamples())
        / static_cast<float>(m_soundData.getSampleRate());
}

size_t Sound::getCurrentOffsetInSamples() const
{
    ALint value { 0 };
    alGetSourcei(m_sourceId, AL_SAMPLE_OFFSET, &value);
    return static_cast<std::size_t>(value);
}

void Sound::markBufferAsQueued(ALuint bufferId)
{
    // internal expectation: bufferId must be in list of all buffers
    assert(std::find(m_bufferIds.cbegin(), m_bufferIds.cend(), bufferId) != m_bufferIds.cend());
    // internal expectation: bufferId must not be in list of unqueued buffer ids
    assert(std::find(m_unqueuedBufferIds.cbegin(), m_unqueuedBufferIds.cend(), bufferId)
        == m_unqueuedBufferIds.cend());

    m_unqueuedBufferIds.push_back(bufferId);
}

void Sound::markBufferAsUnqueued(ALuint bufferId)
{
    // internal expectation: bufferId must be in list of all buffers
    assert(std::find(m_bufferIds.cbegin(), m_bufferIds.cend(), bufferId) != m_bufferIds.cend());
    // internal expectation: bufferId must be in list of unqueued buffer ids
    assert(std::find(m_unqueuedBufferIds.cbegin(), m_unqueuedBufferIds.cend(), bufferId)
        != m_unqueuedBufferIds.cend());

    m_unqueuedBufferIds.erase(
        std::remove(m_unqueuedBufferIds.begin(), m_unqueuedBufferIds.end(), bufferId),
        m_unqueuedBufferIds.end());
}

} // namespace oalpp
