#include "sound.hpp"
#include "sound_context.hpp"
#include "sound_data.hpp"
#include <emscripten.h>
#include <fstream>
#include <iostream>
#include <thread>

std::shared_ptr<Sound> snd;

void main_loop_function()
{
    if (!snd->isPlaying()) {
        //        snd->play();
        std::cout << "is not playing\n";
    } else {
        std::cout << "is playing\n";
    }
}

int main()
{
    std::cout << "pre context\n";
    SoundContext ctx;

    std::cout << "post context\n";

    //    SoundData buf1 { "test1.ogg" };
    std::ifstream infile { "assets/test1.ogg" };
    if (infile.fail()) {
        std::cout << "failed to load file\n";
    }
    std::cout << "post file\n";
    SoundData buf1 { "assets/test1.ogg" };
    std::cout << "post buf\n";
    snd = std::make_shared<Sound>(buf1, ctx);
    std::cout << "post snd\n";
    snd->setVolume(0.25f);

    //    for (float pan = -1.0f; pan <= 1.0f; pan += 2.0f / 7.0f) {
    snd->play();
    //    }

    emscripten_set_main_loop(main_loop_function, 0, 1);

    //    std::cout << "pre while\n";
    //    while (true) { }
    //    SoundData buf2 { "test.mp3" };
    //    Sound snd2 { buf2, ctx };
    //    snd2.setVolume(0.25f);
    //    snd2.play();
    //
    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}
