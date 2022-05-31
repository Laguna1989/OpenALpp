#include "oalpp/effects/filter/moog_filter_stilson.hpp"
#include "oalpp/sound/sound.hpp"
#include "oalpp/sound_context.hpp"
#include "oalpp/sound_data.hpp"
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

    effects::filter::MoogFilterStilson moog { 44100, 1800, 0.5f };

    SoundContext ctx;
    SoundData buffer { fileName };

    SoundDataWithEffect soundDataWithEffect { buffer, moog };

    snd = std::make_shared<Sound>(soundDataWithEffect);
    snd->setVolume(0.5f);
    snd->setIsLooping(true);
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
