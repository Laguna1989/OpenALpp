#ifndef OPENALPP_SOUND_HPP
#define OPENALPP_SOUND_HPP

#include "al.hpp"
#include "sound_data_interface.hpp"
#include <array>
#include <memory>
#include <string>
#include <vector>

namespace oalpp {

// fwd decl.
class SoundContext;

class Sound {
public:
    explicit Sound(SoundDataInterface const& soundData);
    ~Sound();

    void play();
    void stop();
    void pause();
    bool isPlaying() const;

    float getVolume() const;
    void setVolume(float newVolume);

    std::array<float, 3> getPosition() const;

    void setPosition(std::array<float, 3> const& newPos);
    void setPan(float newPan);

    float getPitch() const;
    void setPitch(float const newPitch);

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
    ALuint m_sourceId { 0 };
    ALenum m_format { AL_FORMAT_MONO_FLOAT32 };

    std::size_t m_cursor { 0 };

    float m_volume { 1.0f };
    std::array<float, 3> m_position { 0.0f, 0.0f, -1.0f };
    float m_pitch { 1.0f };

    bool m_isLooping { false };

    void enqueueSamplesToBuffer(ALuint buffer, size_t samplesToQueue);
    void selectSamplesForBuffer(ALuint bufferId);
    void createSource();
    void createBuffers();
    void fillBufferFromStart();
    void deleteSource() const;
    void deleteBuffers();
};

} // namespace oalpp

#endif // OPENALPP_SOUND_HPP
