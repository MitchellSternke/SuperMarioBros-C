#include <cmath>
#include <cstring>

#include <SDL2/SDL.h>

#include "../Configuration.hpp"

#include "APU.hpp"

static const uint8_t lengthTable[] = {
    10, 254, 20, 2, 40, 4, 80, 6, 160, 8, 60, 10, 14, 12, 26, 14,
    12, 16, 24, 18, 48, 20, 96, 22, 192, 24, 72, 26, 16, 28, 32, 30
};

static const uint8_t dutyTable[][8] = {
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 1, 1, 1}
};

static const uint8_t triangleTable[] = {
    15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
};

static const uint16_t noiseTable[] = {
    4, 8, 16, 32, 64, 96, 128, 160, 202, 254, 380, 508, 762, 1016, 2034, 4068
};

/**
 * Pulse waveform generator.
 */
class Pulse
{
    friend class APU;
public:
    Pulse(uint8_t channel)
    {
        enabled = false;
        this->channel = channel;
        lengthEnabled = false;
        lengthValue = 0;
        timerPeriod = 0;
        timerValue = 0;
        dutyMode = 0;
        dutyValue = 0;
        sweepReload = false;
        sweepEnabled = false;
        sweepNegate = false;
        sweepShift = 0;
        sweepPeriod = 0;
        sweepValue = 0;
        envelopeEnabled = false;
        envelopeLoop = false;
        envelopeStart = false;
        envelopePeriod = 0;
        envelopeValue = 0;
        envelopeVolume = 0;
        constantVolume = 0;
    }

    void writeControl(uint8_t value)
    {
        dutyMode = (value >> 6) & 3;
        lengthEnabled = ((value >> 5) & 1) == 0;
        envelopeLoop = ((value >> 5) & 1) == 1;
        envelopeEnabled = ((value >> 4) & 1) == 0;
        envelopePeriod = value & 15;
        constantVolume = value & 15;
        envelopeStart = true;
    }

    void writeSweep(uint8_t value)
    {
        sweepEnabled = ((value >> 7) & 1) == 1;
        sweepPeriod = ((value >> 4) & 7) + 1;
        sweepNegate = ((value >> 3) & 1) == 1;
        sweepShift = value & 7;
        sweepReload = true;
    }

    void writeTimerLow(uint8_t value)
    {
        timerPeriod = (timerPeriod & 0xff00) | (uint16_t)value;
    }

    void writeTimerHigh(uint8_t value)
    {
        lengthValue = lengthTable[value >> 3];
        timerPeriod = (timerPeriod & 0xff) | ((uint16_t)(value & 7) << 8);
        envelopeStart = true;
        dutyValue = 0;
    }

    void stepTimer()
    {
        if (timerValue == 0)
        {
            timerValue = timerPeriod;
            dutyValue = (dutyValue + 1) % 8;
        }
        else
        {
            timerValue--;
        }
    }

    void stepEnvelope()
    {
        if (envelopeStart)
        {
            envelopeVolume = 15;
            envelopeValue = envelopePeriod;
            envelopeStart = false;
        }
        else if (envelopeValue > 0)
        {
            envelopeValue--;
        }
        else
        {
            if (envelopeVolume > 0)
            {
                envelopeVolume--;
            }
            else if (envelopeLoop)
            {
                envelopeVolume = 15;
            }
            envelopeValue = envelopePeriod;
        }
    }

    void stepSweep()
    {
        if (sweepReload)
        {
            if (sweepEnabled && sweepValue == 0)
            {
                sweep();
            }
            sweepValue = sweepPeriod;
            sweepReload = false;
        }
        else if (sweepValue > 0)
        {
            sweepValue--;
        }
        else
        {
            if (sweepEnabled)
            {
                sweep();
            }
            sweepValue = sweepPeriod;
        }
    }

    void stepLength()
    {
        if (lengthEnabled && lengthValue > 0)
        {
            lengthValue--;
        }
    }

    void sweep()
    {
        uint16_t delta = timerPeriod >> sweepShift;
        if (sweepNegate)
        {
            timerPeriod -= delta;
            if (channel == 1)
            {
                timerPeriod--;
            }
        }
        else
        {
            timerPeriod += delta;
        }
    }

    uint8_t output()
    {
        if (!enabled)
        {
            return 0;
        }
        if (lengthValue == 0)
        {
            return 0;
        }
        if (dutyTable[dutyMode][dutyValue] == 0)
        {
            return 0;
        }
        if (timerPeriod < 8 || timerPeriod > 0x7ff)
        {
            return 0;
        }
        if (envelopeEnabled)
        {
            return envelopeVolume;
        }
        else
        {
            return constantVolume;
        }
    }

private:
    bool enabled;
    uint8_t channel;
    bool lengthEnabled;
    uint8_t lengthValue;
    uint16_t timerPeriod;
    uint16_t timerValue;
    uint8_t dutyMode;
    uint8_t dutyValue;
    bool sweepReload;
    bool sweepEnabled;
    bool sweepNegate;
    uint8_t sweepShift;
    uint8_t sweepPeriod;
    uint8_t sweepValue;
    bool envelopeEnabled;
    bool envelopeLoop;
    bool envelopeStart;
    uint8_t envelopePeriod;
    uint8_t envelopeValue;
    uint8_t envelopeVolume;
    uint8_t constantVolume;
};

/**
 * Triangle waveform generator.
 */
class Triangle
{
    friend class APU;
public:
    Triangle()
    {
        enabled = false;
        lengthEnabled = false;
        lengthValue = 0;
        timerPeriod = 0;
        dutyValue = 0;
        counterPeriod = 0;
        counterValue = 0;
        counterReload = false;
    }

    void writeControl(uint8_t value)
    {
        lengthEnabled = ((value >> 7) & 1) == 0;
        counterPeriod = value & 0x7f;
    }

    void writeTimerLow(uint8_t value)
    {
        timerPeriod = (timerPeriod & 0xff00) | (uint16_t)value;
    }

    void writeTimerHigh(uint8_t value)
    {
        lengthValue = lengthTable[value >> 3];
        timerPeriod = (timerPeriod & 0x00ff) | ((uint16_t)(value & 7) << 8);
        timerValue = timerPeriod;
        counterReload = true;
    }

    void stepTimer()
    {
        if (timerValue == 0)
        {
            timerValue = timerPeriod;
            if (lengthValue > 0 && counterValue > 0)
            {
                dutyValue = (dutyValue + 1) % 32;
            }
        }
        else
        {
            timerValue--;
        }
    }

    void stepLength()
    {
        if (lengthEnabled && lengthValue > 0)
        {
            lengthValue--;
        }
    }

    void stepCounter()
    {
        if (counterReload)
        {
            counterValue = counterPeriod;
        }
        else if (counterValue > 0)
        {
            counterValue--;
        }
        if (lengthEnabled)
        {
            counterReload = false;
        }
    }

    uint8_t output()
    {
        if (!enabled)
        {
            return 0;
        }
        if (lengthValue == 0)
        {
            return 0;
        }
        if (counterValue == 0)
        {
            return 0;
        }
        return triangleTable[dutyValue];
    }

private:
    bool enabled;
    bool lengthEnabled;
    uint8_t lengthValue;
    uint16_t timerPeriod;
    uint16_t timerValue;
    uint8_t dutyValue;
    uint8_t counterPeriod;
    uint8_t counterValue;
    bool counterReload;
};

class Noise
{
    friend class APU;
public:
    Noise()
    {
        enabled = false;
        mode = false;
        shiftRegister = 1;
        lengthEnabled = false;
        lengthValue = 0;
        timerPeriod = 0;
        timerValue = 0;
        envelopeEnabled = false;
        envelopeLoop = false;
        envelopeStart = false;
        envelopePeriod = 0;
        envelopeValue = 0;
        envelopeVolume = 0;
        constantVolume = 0;
    }

    void writeControl(uint8_t value)
    {
        lengthEnabled = ((value >> 5) & 1) == 0;
        envelopeLoop = ((value >> 5) & 1) == 1;
        envelopeEnabled = ((value >> 4) & 1) == 0;
        envelopePeriod = value & 15;
        constantVolume = value & 15;
        envelopeStart = true;
    }

    void writePeriod(uint8_t value)
    {
        mode = (value & 0x80) == 0x80;
        timerPeriod = noiseTable[value & 0x0f];
    }

    void writeLength(uint8_t value)
    {
        lengthValue = lengthTable[value >> 3];
        envelopeStart = true;
    }

    void stepTimer()
    {
        if (timerValue == 0)
        {
            timerValue = timerPeriod;
            uint8_t shift;
            if (mode)
            {
                shift = 6;
            }
            else
            {
                shift = 1;
            }
            uint16_t b1 = shiftRegister & 1;
            uint16_t b2 = (shiftRegister >> shift) & 1;
            shiftRegister >>= 1;
            shiftRegister |= (b1 ^ b2) << 14;
        }
        else
        {
            timerValue--;
        }
    }

    void stepEnvelope()
    {
        if (envelopeStart)
        {
            envelopeVolume = 15;
            envelopeValue = envelopePeriod;
            envelopeStart = false;
        }
        else if (envelopeValue > 0)
        {
            envelopeValue--;
        }
        else
        {
            if (envelopeVolume > 0)
            {
                envelopeVolume--;
            }
            else if (envelopeLoop)
            {
                envelopeVolume = 15;
            }
            envelopeValue = envelopePeriod;
        }
    }

    void stepLength()
    {
        if (lengthEnabled && lengthValue > 0)
        {
            lengthValue--;
        }
    }

    uint8_t output()
    {
        if (!enabled)
        {
            return 0;
        }
        if (lengthValue == 0)
        {
            return 0;
        }
        if ((shiftRegister & 1) == 1)
        {
            return 0;
        }
        if (envelopeEnabled)
        {
            return envelopeVolume;
        }
        else
        {
            return constantVolume;
        }
    }

private:
    bool enabled;
    bool mode;
    uint16_t shiftRegister;
    bool lengthEnabled;
    uint8_t lengthValue;
    uint16_t timerPeriod;
    uint16_t timerValue;
    bool envelopeEnabled;
    bool envelopeLoop;
    bool envelopeStart;
    uint8_t envelopePeriod;
    uint8_t envelopeValue;
    uint8_t envelopeVolume;
    uint8_t constantVolume;
};

APU::APU()
{
    frameValue = 0;
    audioBufferLength = 0;

    pulse1 = new Pulse(1);
    pulse2 = new Pulse(2);
    triangle = new Triangle;
    noise = new Noise;
}

APU::~APU()
{
    delete pulse1;
    delete pulse2;
    delete triangle;
    delete noise;
}

uint8_t APU::getOutput()
{
    double pulseOut = 0.00752 * (pulse1->output() + pulse2->output());
    double tndOut = 0.00851 * triangle->output() + 0.00494 * noise->output();

    return static_cast<uint8_t>(floor(255.0 * (pulseOut + tndOut)));
}

void APU::output(uint8_t* buffer, int len)
{
    len = (len > audioBufferLength) ? audioBufferLength : len;
    memcpy(buffer, audioBuffer, len);
    if (len > audioBufferLength)
    {
        memcpy(buffer, audioBuffer, audioBufferLength);
        audioBufferLength = 0;
    }
    else
    {
        memcpy(buffer, audioBuffer, len);
        audioBufferLength -= len;
        memcpy(audioBuffer, audioBuffer + len, audioBufferLength);
    }
}

void APU::stepFrame()
{
    // Step the frame counter 4 times per frame, for 240Hz
    for (int i = 0; i < 4; i++)
    {
        frameValue = (frameValue + 1) % 5;
        switch (frameValue)
        {
        case 1:
        case 3:
            stepEnvelope();
            break;
        case 0:
        case 2:
            stepEnvelope();
            stepSweep();
            stepLength();
            break;
        }

        // Calculate the number of samples needed per 1/4 frame
        //
        int frequency = Configuration::getAudioFrequency();

        // Example: we need 735 samples per frame for 44.1KHz sound sampling
        //
        int samplesToWrite = frequency / (Configuration::getFrameRate() * 4);
        if (i == 3)
        {
            // Handle the remainder on the final tick of the frame counter
            //
            samplesToWrite = (frequency / Configuration::getFrameRate()) - 3 * (frequency / (Configuration::getFrameRate() * 4));
        }
        
        SDL_LockAudio();

        // Step the timer ~3729 times per quarter frame for most channels
        //
        int j = 0;
        for (int stepIndex = 0; stepIndex < 3729; stepIndex++)
        {
            if (j < samplesToWrite &&
                (stepIndex / 3729.0) > (j / (double)samplesToWrite))
            {
                uint8_t sample = getOutput();
                audioBuffer[audioBufferLength + j] = sample;
                j++;
            }

            pulse1->stepTimer();
            pulse2->stepTimer();
            noise->stepTimer();
            triangle->stepTimer();
            triangle->stepTimer();
        }
        audioBufferLength += samplesToWrite;
        
        SDL_UnlockAudio();
    }
}

void APU::stepEnvelope()
{
    pulse1->stepEnvelope();
    pulse2->stepEnvelope();
    triangle->stepCounter();
    noise->stepEnvelope();
}

void APU::stepSweep()
{
    pulse1->stepSweep();
    pulse2->stepSweep();
}

void APU::stepLength()
{
    pulse1->stepLength();
    pulse2->stepLength();
    triangle->stepLength();
    noise->stepLength();
}

void APU::writeControl(uint8_t value)
{
    pulse1->enabled = (value & 1) == 1;
    pulse2->enabled = (value & 2) == 2;
    triangle->enabled = (value & 4) == 4;
    noise->enabled = (value & 8) == 8;
    if (!pulse1->enabled)
    {
        pulse1->lengthValue = 0;
    }
    if (!pulse2->enabled)
    {
        pulse2->lengthValue = 0;
    }
    if (!triangle->enabled)
    {
        triangle->lengthValue = 0;
    }
    if (!noise->enabled)
    {
        noise->lengthValue = 0;
    }
}

void APU::writeRegister(uint16_t address, uint8_t value)
{
    switch (address)
    {
    case 0x4000:
        pulse1->writeControl(value);
        break;
    case 0x4001:
        pulse1->writeSweep(value);
        break;
    case 0x4002:
        pulse1->writeTimerLow(value);
        break;
    case 0x4003:
        pulse1->writeTimerHigh(value);
        break;
    case 0x4004:
        pulse2->writeControl(value);
        break;
    case 0x4005:
        pulse2->writeSweep(value);
        break;
    case 0x4006:
        pulse2->writeTimerLow(value);
        break;
    case 0x4007:
        pulse2->writeTimerHigh(value);
        break;
    case 0x4008:
        triangle->writeControl(value);
        break;
    case 0x400a:
        triangle->writeTimerLow(value);
        break;
    case 0x400b:
        triangle->writeTimerHigh(value);
        break;
    case 0x400c:
        noise->writeControl(value);
        break;
    case 0x400d:
    case 0x400e:
        noise->writePeriod(value);
        break;
    case 0x400f:
        noise->writeLength(value);
        break;
    case 0x4015:
        writeControl(value);
        break;
    case 0x4017:
        stepEnvelope();
        stepSweep();
        stepLength();
    default:
        break;
    }
}
