#include "sound.hpp"
#include "sound_context.hpp"
#include <thread>

int main()
{
    SoundContext ctx;

    Sound snd1 { "test1.ogg" };
    snd1.play();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    return 0;
}
