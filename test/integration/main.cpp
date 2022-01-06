#include "sound.hpp"
#include "sound_context.hpp"
#include "sound_data.hpp"
#include <thread>

int main()
{
    SoundContext ctx;

    SoundData buf1 { "test1.ogg" };
    Sound snd1 { buf1, ctx };
    snd1.setVolume(0.25f);
    snd1.play();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    SoundData buf2 { "test.mp3" };
    Sound snd2 { buf2, ctx };
    snd2.setVolume(0.25f);
    snd2.play();

    std::this_thread::sleep_for(std::chrono::milliseconds(9000));

    return 0;
}
