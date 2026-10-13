/**
 * @file
 * @brief Audio playback.
 */
#ifndef AUDIOOUTPUT_HPP
#define AUDIOOUTPUT_HPP

#include <cstdint>
#include <vector>

#include <SDL.h>

/**
 * Plays the game's audio through an SDL audio queue.
 */
class AudioOutput
{
public:
    /**
     * Open the default audio device. If that fails, the error is logged and the output stays closed.
     *
     * @param sampleRate the sample rate in Hz.
     * @param volume the volume, from 0 to 100.
     */
    AudioOutput(int sampleRate, int volume);
    ~AudioOutput();

    AudioOutput(const AudioOutput&) = delete;
    AudioOutput& operator=(const AudioOutput&) = delete;

    bool isOpen() const;

    /**
     * Queue samples for playback.
     */
    void play(const std::vector<int16_t>& samples);

    /**
     * Stop playback and discard queued samples (when paused), or resume it.
     */
    void setPaused(bool paused);

    void toggleMute();

private:
    SDL_AudioDeviceID device = 0;
    int sampleRate;
    int volume;
    bool muted = false;
    std::vector<int16_t> buffer;
};

#endif // AUDIOOUTPUT_HPP
