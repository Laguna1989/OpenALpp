#include "sound_context.hpp"
#include "sound.hpp"

int main()
{
    SoundContext ctx;

    Sound snd{"test.ogg"};
    snd.play();
    return 0;
}
