#include "oalpp/effects/distortion/tanh_distortion.hpp"
#include "oalpp/effects/filter/butterworth_24db_lowpass.hpp"
#include "oalpp/effects/filter/simple_highpass.hpp"
#include "oalpp/effects/utility/convolution.hpp"
#include "oalpp/effects/utility/dj_fft.h"
#include "oalpp/effects/utility/effect_chain.hpp"
#include "oalpp/effects/utility/gain.hpp"
#include "oalpp/sound.hpp"
#include "oalpp/sound_context.hpp"
#include "oalpp/sound_data.hpp"
#include "oalpp/sound_data/sound_data_left_to_mono.hpp"
#include "oalpp/sound_data/sound_data_text_writer.hpp"

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

    effects::filter::SimpleHighpass highpass { 44100, 150, 2.0f };
    effects::distortion::TanhDistortion dist { 10.0f, 0.7f };
    effects::filter::Butterworth24dbLowpass lowpass { 44100, 9000.0f, 0.0f };

    SoundData kernel { "assets/kernel.wav" };
    SoundDataLeftToMono kernelLeft(kernel);
    effects::utility::Convolution conv { kernelLeft.getSamples() };

    effects::utility::Gain gain { 2.0f };

    SoundContext ctx;
    SoundData buffer { fileName };

    effects::utility::EffectChain::EffectsT effects { highpass, conv, dist, lowpass, gain };
    effects::utility::EffectChain effectChain { effects };

    SoundDataWithEffect soundDataWithEffect { buffer, effectChain };

    SoundDataWithEffect convoluted { soundDataWithEffect, conv };

    snd = std::make_shared<Sound>(soundDataWithEffect);
    snd->setVolume(0.5f);
    snd->setIsLooping(true);
    snd->play();

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop_function, 0, 1);
#else
    while (snd->isPlaying()) {
        //        main_loop_function();
        snd->update();
    }
#endif
    snd.reset();
    return 0;
}
