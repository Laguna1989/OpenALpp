#include "sound.hpp"
#include "sound_context.hpp"
#include "sound_data.hpp"
#include <fstream>
#include <iostream>
#include <thread>

int main()
{
    std::cout << "pre context\n";
    SoundContext ctx;

    std::cout << "post context\n";

    //    SoundData buf1 { "test1.ogg" };
    std::ifstream infile { "test1.ogg" };
    if (infile.fail()) {
        std::cout << "failed to load file\n";
    }
    std::cout << "post file\n";

    //    Sound snd1 { buf1, ctx };
    //    snd1.setVolume(0.25f);
    //
    //    for (float pan = -1.0f; pan <= 1.0f; pan += 2.0f / 7.0f) {
    //        snd1.setPan(pan);
    //        snd1.play();
    //
    //        //        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //    }
    //    while (true) { }
    //    SoundData buf2 { "test.mp3" };
    //    Sound snd2 { buf2, ctx };
    //    snd2.setVolume(0.25f);
    //    snd2.play();
    //
    //    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return 0;
}
