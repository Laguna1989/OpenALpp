#include "sound.hpp"
#include "sound_context.hpp"

int main()
{
    SoundContext ctx;

    Sound snd1 { "test1.ogg" };
    snd1.play();

    Sound snd2 { "test2.ogg" };
    snd2.play();

    return 0;
}
