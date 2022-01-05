#include "sound.hpp"
#include "sound_context.hpp"
#include <thread>

int main()
{
    SoundContext ctx;

    Sound snd1 { "test1.ogg" };
    snd1.play();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // figure out why this stops after a time. Might be a buffer issue (perhaps this will be fixed
    // with streaming audio)
    Sound snd2 { "test.mp3" };
    snd2.play();

    std::this_thread::sleep_for(std::chrono::milliseconds(9000));

    return 0;
}
