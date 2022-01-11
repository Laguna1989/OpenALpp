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
    explicit Sound(SoundDataInterface const& soundData, SoundContext const& ctx);
    ~Sound();
    void play();
    bool isPlaying() const;

    float getVolume() const;
    void setVolume(float newVolume);

    std::array<float, 3> getPosition() const;

    void setPosition(std::array<float, 3> const& newPos);
    void setPan(float newPan);

    float getPitch() const;

    void setPitch(float const newPitch);

    void update();

private:
    std::array<ALuint, 6> m_bufferIds { 0 };
    ALuint m_sourceId { 0 };

    std::size_t m_cursor { 0 };

    float m_volume { 1.0f };
    std::array<float, 3> m_position { 0.0f, 0.0f, -1.0f };
    float m_pitch { 1.0f };
};

} // namespace oalpp

#endif // OPENALPP_SOUND_HPP
