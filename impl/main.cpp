#include "sound.hpp"
#include "sound_context.hpp"
#include <thread>

int main()
{
    SoundContext ctx;

    Sound snd1 { "test1.ogg" };
    snd1.play();

    Sound snd2 { "test2.ogg" };
    snd2.play();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;
}
