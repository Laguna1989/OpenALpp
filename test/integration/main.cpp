#include "oalpp/effects/filter/filter_butterworth_24_d_b.hpp"
#include "oalpp/sound.hpp"
#include "oalpp/sound_context.hpp"
#include "oalpp/sound_data.hpp"
#include "oalpp/sound_data_with_effect.hpp"
#include <fstream>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace oalpp;

std::shared_ptr<Sound> snd;

void main_loop_function()
{
    if (snd->isPlaying()) {
        snd->update();
    } else {
    }
}

int main()
{
    std::string const fileName { "assets/test.mp3" };

    std::ifstream file { fileName };
    if (file.fail()) {
        std::cerr << "Error opening test audio file.\nCopy assets folder from source root next to "
                     "executable for this test to work\n";
        return 1;
    }

    SoundContext ctx;
    SoundData buffer { fileName };
    // TODO sample rate int <-> float
    effects::filter::FilterButterworth24db filter { static_cast<float>(buffer.getSampleRate()),
        1000.0f, 0.0f };
    SoundDataWithEffect soundDataWithEffect { buffer, filter };

    snd = std::make_shared<Sound>(soundDataWithEffect, ctx);
    snd->setVolume(0.25f);
    snd->play();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop_function, 0, 1);
#else
    while (snd->isPlaying()) {
        main_loop_function();
    }
#endif
    snd.reset();
    return 0;
}
