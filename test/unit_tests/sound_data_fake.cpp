#include "sound_data_fake.hpp"

int SoundDataMonoFake::getNumberOfChannels() const { return 1; }

int SoundDataMonoFake::getSampleRate() const { return 44100; }

std::vector<float> const& SoundDataMonoFake::getSamples() const { return m_samples; }

int SoundDataStereoFake::getNumberOfChannels() const { return 2; }

int SoundDataStereoFake::getSampleRate() const { return 44100; }

std::vector<float> const& SoundDataStereoFake::getSamples() const { return m_samples; }
