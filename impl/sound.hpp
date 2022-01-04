#ifndef OPENALTRYOUT_SOUND_HPP
#define OPENALTRYOUT_SOUND_HPP

#include "al.hpp"
#include <memory>
#include <string>
#include <vector>

class Sound {
public:
    explicit Sound(const std::string& fileName);
    ~Sound() = default;
    void play();
    bool isPlaying() const;

private:
    ALuint m_bufferId { 0 };
    std::vector<short> m_buffer;
    ALuint m_sourceId { 0 };
};

#endif // OPENALTRYOUT_SOUND_HPP
