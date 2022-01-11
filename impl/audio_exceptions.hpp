#ifndef OPENALPP_AUDIO_EXCEPTIONS_HPP
#define OPENALPP_AUDIO_EXCEPTIONS_HPP

#include <stdexcept>

namespace oalpp {
class AudioException : public std::exception {
public:
    explicit AudioException(char const* const message)
        : m_message { message }
    {
    }

    [[nodiscard]] char const* what() const override { return m_message; }

private:
    char const* m_message;
};

class AudioSystemException : public std::exception {
public:
    explicit AudioSystemException(char const* const message)
        : m_message { message }
    {
    }

    [[nodiscard]] char const* what() const override { return m_message; }

private:
    char const* m_message;
};

} // namespace oalpp

#endif // OPENALPP_AUDIO_EXCEPTIONS_HPP
