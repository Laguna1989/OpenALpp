#include "audio_exceptions.hpp"

char const* oalpp::AudioException::what() const noexcept { return m_message.c_str(); }

char const* oalpp::AudioSystemException::what() const noexcept { return m_message.c_str(); }
