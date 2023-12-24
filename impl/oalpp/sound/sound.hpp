#ifndef OPENALPP_SOUND_HPP
#define OPENALPP_SOUND_HPP

#include <oalpp/common/al.hpp>
#include <oalpp/sound/position.hpp>
#include <oalpp/sound_data/sound_data_interface.hpp>
#include <array>
#include <list>

namespace oalpp {

class Sound {
public:
    explicit Sound(SoundDataInterface const& soundData);
    ~Sound();

    void play();
    void stop();
    void pause() const;
    bool isPlaying() const;

    float getVolume() const;
    void setVolume(float newVolume);

    Position getPosition() const;

    void setPosition(Position const& newPosition);
    void setPan(float newPan);

    float getPitch() const;
    void setPitch(float newPitch);

    bool getIsLooping() const;
    void setIsLooping(bool value);

    void update();

    std::size_t getLengthInSamples() const;
    float getLengthInSeconds() const;

    float getCurrentOffsetInSeconds() const;

    std::size_t getCurrentOffsetInSamples() const;

    static constexpr std::size_t BUFFER_SIZE = 65536u;
    static constexpr std::size_t BUFFER_COUNT = 4u;

private:
    SoundDataInterface const& m_soundData;

    std::array<ALuint, BUFFER_COUNT> m_bufferIds { 0 };

    // buffers that are not queued at the moment
    // Note: Needs to be a list as this is modified while being iterated
    std::list<ALuint> m_unqueuedBufferIds {};
    ALuint m_sourceId { 0 };
    ALenum m_format { AL_FORMAT_MONO_FLOAT32 };

    std::size_t m_cursor { 0 };

    float m_volume { 1.0f };
    Position m_position { 0.0f, 0.0f, -1.0f };
    float m_pitch { 1.0f };

    bool m_isLooping { false };

    void enqueueSamplesToBuffer(ALuint bufferId, size_t samplesToQueue);
    void selectSamplesForBuffer(ALuint bufferId);
    bool hasDataToEnqueue() const;
    bool hasDataForFullBufferToEnqueue() const;

    void initSourceAndBuffers();
    void deleteSourceAndBuffers();

    ALint getNumberOfBuffersProcessed() const;
    // buffers that are not currently queued
    std::list<ALuint> getUnqueuedBufferIds() const;
    void markBufferAsQueued(ALuint bufferId);
    void markBufferAsUnqueued(ALuint bufferId);
};

} // namespace oalpp

#endif // OPENALPP_SOUND_HPP
