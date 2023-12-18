#include "sound_data_helper.hpp"

namespace oalpp {

std::string to_string(SoundData const& soundData)
{
    std::string str = "# Sound Data\n";
    str += "# sampleRate: " + std::to_string(soundData.getSampleRate()) + "\n";
    str += "# numberOfChannels: " + std::to_string(soundData.getNumberOfChannels()) + "\n";

    for (auto index = 0U; index != soundData.getSamples().size(); ++index) {
        str += std::to_string(index) + " " + std::to_string(soundData.getSamples()[index]) + "\n";
    }
    str += "\n";

    return str;
}

} // namespace oalpp
