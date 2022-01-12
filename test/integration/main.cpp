#include "sound.hpp"
#include "sound_context.hpp"
#include "sound_data.hpp"
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace oalpp;

std::shared_ptr<Sound> snd;

void main_loop_function()
{
    if (snd->isPlaying()) {
        //        std::cout << "is playing\n";
        snd->update();
    } else {
        //        std::cout << "is not playing\n";
    }
}

int main()
{
    SoundContext ctx;
    SoundData buf1 { "assets/test.mp3" };

    snd = std::make_shared<Sound>(buf1, ctx);
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
