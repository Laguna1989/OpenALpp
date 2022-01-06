#ifndef OPENALTRYOUT_SOUND_HPP
#define OPENALTRYOUT_SOUND_HPP

#include "al.hpp"
#include "sound_data_interface.hpp"
#include <memory>
#include <string>
#include <vector>

// fwd decl.
class SoundContext;

class Sound {
public:
    explicit Sound(SoundDataInterface const& buffer, SoundContext const& ctx);
    ~Sound();
    void play();
    bool isPlaying() const;

private:
    ALuint m_bufferId { 0 };
    ALuint m_sourceId { 0 };
};

#endif // OPENALTRYOUT_SOUND_HPP
