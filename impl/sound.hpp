#ifndef OPENALTRYOUT_SOUND_HPP
#define OPENALTRYOUT_SOUND_HPP

#include "al.hpp"
#include <string>

class Sound {
public:
    explicit Sound(const std::string& fileName);
    ~Sound() = default;
    void play();

private:
    ALuint buffer { 0 };
    short* output { nullptr };
    ALuint source { 0 };
};

#endif // OPENALTRYOUT_SOUND_HPP
