#include "sound_data_text_writer.hpp"

namespace oalpp {

SoundDataTextWriter::SoundDataTextWriter(SoundDataInterface& soundData)
    : m_soundData { soundData }
{
}

std::string SoundDataTextWriter::getText() const
{
    std::string str = "# Sound Data\n";
    str += "# SampleRate: " + std::to_string(m_soundData.getSampleRate()) + "\n";

    for (auto index = 0U; index != m_soundData.getSamples().size(); ++index) {
        str += std::to_string(index) + " " + std::to_string(m_soundData.getSamples()[index]) + "\n";
    }
    str += "\n";
    return str;
}

} // namespace oalpp
