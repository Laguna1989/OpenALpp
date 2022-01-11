#ifndef OPENALPP_AUDIO_EXCEPTIONS_HPP
#define OPENALPP_AUDIO_EXCEPTIONS_HPP

#include <stdexcept>

namespace oalpp
{
class AudioException : public std::exception
{
public:
    explicit AudioException(char const* const message)
        : exception(message)
    {
    }
};

class AudioSystemException : public std::exception
{
public:
    explicit AudioSystemException(char const* const message)
        : exception(message)
    {
    }
};

}

#endif // OPENALPP_AUDIO_EXCEPTIONS_HPP
