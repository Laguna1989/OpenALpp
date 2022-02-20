#ifndef OPENALPP_SOUND_DATA_TEXT_WRITER_HPP
#define OPENALPP_SOUND_DATA_TEXT_WRITER_HPP

#include "sound_data_interface.hpp"
#include <string>

namespace oalpp {
class SoundDataTextWriter {
public:
    explicit SoundDataTextWriter(SoundDataInterface& soundData);
    std::string getText() const;

    SoundDataInterface& m_soundData;
};

} // namespace oalpp
#endif // OPENALPP_SOUND_DATA_TEXT_WRITER_HPP
