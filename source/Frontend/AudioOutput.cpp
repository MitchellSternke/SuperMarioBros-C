#include <algorithm>
#include <iostream>

#include "AudioOutput.hpp"

namespace
{

/**
 * Most audio that may be waiting to be played, in seconds. Beyond this (e.g. after the game
 * stalled, or if the display runs faster than the audio device), samples are dropped to keep
 * the sound in sync with the picture.
 */
constexpr double MAX_LATENCY = 0.1;

} // namespace

AudioOutput::AudioOutput(int sampleRate, int volume) :
    sampleRate(sampleRate),
    volume(std::clamp(volume, 0, 100))
{
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "Audio is unavailable: " << SDL_GetError() << "\n";
        return;
    }

    SDL_AudioSpec desired{};
    desired.freq = sampleRate;
    desired.format = AUDIO_S16SYS;
    desired.channels = 1;
    desired.samples = 1024;

    // No changes allowed: SDL converts to whatever the hardware needs
    device = SDL_OpenAudioDevice(nullptr, 0, &desired, nullptr, 0);
    if (device == 0)
    {
        std::cerr << "Unable to open the audio device: " << SDL_GetError() << "\n";
        return;
    }
    SDL_PauseAudioDevice(device, 0);
}

AudioOutput::~AudioOutput()
{
    if (device != 0)
    {
        SDL_CloseAudioDevice(device);
    }
}

bool AudioOutput::isOpen() const
{
    return device != 0;
}

void AudioOutput::play(const std::vector<int16_t>& samples)
{
    if (device == 0)
    {
        return;
    }

    const auto maxQueued = static_cast<Uint32>(sampleRate * MAX_LATENCY) * sizeof(int16_t);
    if (SDL_GetQueuedAudioSize(device) > maxQueued)
    {
        return;
    }

    const int gain = muted ? 0 : volume;
    buffer.resize(samples.size());
    std::transform(samples.begin(), samples.end(), buffer.begin(),
                   [gain](int16_t sample) { return static_cast<int16_t>(sample * gain / 100); });
    SDL_QueueAudio(device, buffer.data(), static_cast<Uint32>(buffer.size() * sizeof(int16_t)));
}

void AudioOutput::setPaused(bool paused)
{
    if (device == 0)
    {
        return;
    }
    if (paused)
    {
        SDL_ClearQueuedAudio(device);
    }
    SDL_PauseAudioDevice(device, paused ? 1 : 0);
}

void AudioOutput::toggleMute()
{
    muted = !muted;
}
