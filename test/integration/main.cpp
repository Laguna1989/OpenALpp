#include "sound.hpp"
#include "sound_context.hpp"
#include "sound_data.hpp"
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace oalpp;

std::shared_ptr<Sound> snd;

std::size_t const NUM_BUFFERS = 4;
std::size_t const BUFFER_SIZE = 65536u;

void main_loop_function()
{
    if (!snd->isPlaying()) {
        std::cout << "is not playing\n";
    } else {
        std::cout << "is playing\n";
    }
}

void update_stream(const ALuint source, const ALenum& format, const std::int32_t& sampleRate,
    const std::vector<char>& soundData, std::size_t& cursor)
{
    ALint buffersProcessed = 0;
    alGetSourcei(source, AL_BUFFERS_PROCESSED, &buffersProcessed);

    if (buffersProcessed <= 0)
        return;

    while (buffersProcessed--) {
        ALuint buffer;
        alSourceUnqueueBuffers(source, 1, &buffer);

        ALsizei dataSize = BUFFER_SIZE;

        char* data = new char[dataSize];
        std::memset(data, 0, dataSize);

        std::size_t dataSizeToCopy = BUFFER_SIZE;
        if (cursor + BUFFER_SIZE > soundData.size())
            dataSizeToCopy = soundData.size() - cursor;

        std::memcpy(&data[0], &soundData[cursor], dataSizeToCopy);
        cursor += dataSizeToCopy;

        if (dataSizeToCopy < BUFFER_SIZE) {
            cursor = 0;
            std::memcpy(&data[dataSizeToCopy], &soundData[cursor], BUFFER_SIZE - dataSizeToCopy);
            cursor = BUFFER_SIZE - dataSizeToCopy;
        }

        alBufferData(buffer, format, data, BUFFER_SIZE, sampleRate);
        alSourceQueueBuffers(source, 1, &buffer);

        delete[] data;
    }
}

int main()
{
    SoundContext ctx;
    SoundData buf1 { "assets/test.mp3" };

    ALuint buffers[NUM_BUFFERS];
    alGenBuffers(NUM_BUFFERS, &buffers[0]);
    ALenum format = AL_FORMAT_MONO16;
    if (buf1.getNumberOfChannels() == 2) {
        format = AL_FORMAT_STEREO16;
    }

    for (std::size_t i = 0; i < NUM_BUFFERS; ++i) {
        alBufferData(buffers[i], format, &(buf1.getSamples()[i * BUFFER_SIZE]), BUFFER_SIZE,
            buf1.getSampleRate());
    }

    ALuint source;
    alGenSources(1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1.0f);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);

    alSourceQueueBuffers(source, NUM_BUFFERS, &buffers[0]);
    alSourcePlay(source);

    ALint state = AL_PLAYING;
    std::size_t cursor = BUFFER_SIZE * NUM_BUFFERS;

    while (state == AL_PLAYING) {
        update_stream(source, format, buf1.getSampleRate(), buf1.getSamples(), cursor);
        alGetSourcei(source, AL_SOURCE_STATE, &state);
    }

    alDeleteSources(1, &source);
    alDeleteBuffers(NUM_BUFFERS, &buffers[0]);

    //    snd = std::make_shared<Sound>(buf1, ctx);
    //    snd->setVolume(0.25f);
    //    snd->setPitch(0.8f);
    //    snd->play();
    //#ifdef __EMSCRIPTEN__
    //    emscripten_set_main_loop(main_loop_function, 0, 1);
    //#else
    //    while (snd->isPlaying()) {
    //        main_loop_function();
    //    }
    //#endif
    //    snd.reset();
    return 0;
}
