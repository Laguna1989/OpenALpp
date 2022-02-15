#ifndef OPENALPP_AUDIO_EXCEPTIONS_HPP
#define OPENALPP_AUDIO_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>
#include <utility>

namespace oalpp {
class AudioException : public std::exception {
public:
    explicit AudioException(std::string message)
        : m_message { std::move(message) }
    {
    }

    [[nodiscard]] char const* what() const noexcept override { return m_message.c_str(); }

private:
    std::string m_message;
};

class AudioSystemException : public std::exception {
public:
    explicit AudioSystemException(std::string message)
        : m_message { std::move(message) }
    {
    }

    [[nodiscard]] char const* what() const noexcept override { return m_message.c_str(); }

private:
    std::string m_message;
};

} // namespace oalpp

#endif // OPENALPP_AUDIO_EXCEPTIONS_HPP
