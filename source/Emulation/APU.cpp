#include <algorithm>
#include <array>
#include <cmath>

#include "APU.hpp"

namespace
{

const uint8_t lengthTable[] = {
    10, 254, 20, 2, 40, 4, 80, 6, 160, 8, 60, 10, 14, 12, 26, 14,
    12, 16, 24, 18, 48, 20, 96, 22, 192, 24, 72, 26, 16, 28, 32, 30
};

const uint8_t dutyTable[][8] = {
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 1, 1, 1}
};

const uint8_t triangleTable[] = {
    15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
};

const uint16_t noiseTable[] = {
    4, 8, 16, 32, 64, 96, 128, 160, 202, 254, 380, 508, 762, 1016, 2034, 4068
};

/**
 * Number of channel timer steps per quarter frame.
 */
constexpr int STEPS_PER_QUARTER_FRAME = 3729;

/**
 * Audio is processed in fixed point, with 1.0 represented by this value, so that the
 * output is identical on every platform.
 */
constexpr int FIXED_ONE = 1 << 16;

/**
 * The NES mixes its channels nonlinearly. These tables approximate the mixer's output
 * (as a fraction of FIXED_ONE) for the sum of the pulse channels, and for the weighted
 * sum 3 * triangle + 2 * noise (+ DMC, which Super Mario Bros. does not use).
 * See https://www.nesdev.org/wiki/APU_Mixer
 */
struct MixerTables
{
    std::array<int, 31> pulse{};
    std::array<int, 203> tnd{};

    MixerTables()
    {
        for (std::size_t n = 1; n < pulse.size(); n++)
        {
            pulse[n] = static_cast<int>(std::lround(FIXED_ONE * 95.52 / (8128.0 / n + 100.0)));
        }
        for (std::size_t n = 1; n < tnd.size(); n++)
        {
            tnd[n] = static_cast<int>(std::lround(FIXED_ONE * 163.67 / (24329.0 / n + 100.0)));
        }
    }
};

const MixerTables mixer;

/**
 * Converts a fixed-point sample to signed 16 bits, with headroom for the loudest passages.
 */
constexpr int OUTPUT_GAIN_NUMERATOR = 7;
constexpr int OUTPUT_GAIN_DENOMINATOR = 4;

/**
 * Silences a channel after a number of quarter frames.
 */
struct LengthCounter
{
    bool enabled = false;
    uint8_t value = 0;

    void load(uint8_t registerValue)
    {
        value = lengthTable[registerValue >> 3];
    }

    void step()
    {
        if (enabled && value > 0)
        {
            value--;
        }
    }
};

/**
 * Volume envelope shared by the pulse and noise channels.
 */
struct Envelope
{
    bool enabled = false; /**< When disabled, the channel plays at a constant volume. */
    bool loop = false;
    bool start = false;
    uint8_t period = 0;
    uint8_t value = 0;
    uint8_t volume = 0;
    uint8_t constantVolume = 0;

    void writeControl(uint8_t control)
    {
        loop = ((control >> 5) & 1) == 1;
        enabled = ((control >> 4) & 1) == 0;
        period = control & 15;
        constantVolume = control & 15;
        start = true;
    }

    void step()
    {
        if (start)
        {
            volume = 15;
            value = period;
            start = false;
        }
        else if (value > 0)
        {
            value--;
        }
        else
        {
            if (volume > 0)
            {
                volume--;
            }
            else if (loop)
            {
                volume = 15;
            }
            value = period;
        }
    }

    uint8_t output() const
    {
        return enabled ? volume : constantVolume;
    }
};

} // namespace

/**
 * The analog output stage of the NES: two first-order high-pass filters (90 Hz and 440 Hz),
 * which also remove the DC offset of the mixer output, and a first-order low-pass filter (14 kHz).
 */
class OutputFilter
{
public:
    explicit OutputFilter(int sampleRate) :
        highPass90(highPassCoefficient(90.0, sampleRate)),
        highPass440(highPassCoefficient(440.0, sampleRate)),
        lowPass14k(lowPassCoefficient(14000.0, sampleRate))
    {
    }

    /**
     * Filter a mixer output sample (fixed point) and convert it to 16 bits.
     */
    int16_t process(int input)
    {
        const int64_t stage1 = highPass(input, highPass90, input1, output1);
        const int64_t stage2 = highPass(stage1, highPass440, input2, output2);
        output3 += (lowPass14k * (stage2 - output3)) / FIXED_ONE;

        const int64_t sample = output3 * 32767 * OUTPUT_GAIN_NUMERATOR / (int64_t{FIXED_ONE} * OUTPUT_GAIN_DENOMINATOR);
        return static_cast<int16_t>(std::clamp<int64_t>(sample, -32768, 32767));
    }

private:
    int64_t highPass90;
    int64_t highPass440;
    int64_t lowPass14k;
    int64_t input1 = 0;
    int64_t output1 = 0;
    int64_t input2 = 0;
    int64_t output2 = 0;
    int64_t output3 = 0;

    static constexpr double PI = 3.14159265358979323846;

    static int64_t highPassCoefficient(double cutoff, int sampleRate)
    {
        // RC / (RC + dt)
        return std::lround(FIXED_ONE / (1.0 + 2.0 * PI * cutoff / sampleRate));
    }

    static int64_t lowPassCoefficient(double cutoff, int sampleRate)
    {
        // dt / (RC + dt)
        return std::lround(FIXED_ONE / (1.0 + sampleRate / (2.0 * PI * cutoff)));
    }

    static int64_t highPass(int64_t input, int64_t coefficient, int64_t& previousInput, int64_t& previousOutput)
    {
        previousOutput = (coefficient * (previousOutput + input - previousInput)) / FIXED_ONE;
        previousInput = input;
        return previousOutput;
    }
};

/**
 * Pulse waveform generator.
 */
class Pulse
{
public:
    bool enabled = false;
    LengthCounter length;

    explicit Pulse(uint8_t channel) :
        channel(channel)
    {
    }

    void writeControl(uint8_t value)
    {
        dutyMode = (value >> 6) & 3;
        length.enabled = ((value >> 5) & 1) == 0;
        envelope.writeControl(value);
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
        timerPeriod = (timerPeriod & 0xff00) | value;
    }

    void writeTimerHigh(uint8_t value)
    {
        length.load(value);
        timerPeriod = (timerPeriod & 0x00ff) | ((value & 7) << 8);
        envelope.start = true;
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
        envelope.step();
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

    uint8_t output() const
    {
        if (!enabled || length.value == 0 || dutyTable[dutyMode][dutyValue] == 0 ||
            timerPeriod < 8 || timerPeriod > 0x7ff)
        {
            return 0;
        }
        return envelope.output();
    }

private:
    uint8_t channel;
    Envelope envelope;
    uint16_t timerPeriod = 0;
    uint16_t timerValue = 0;
    uint8_t dutyMode = 0;
    uint8_t dutyValue = 0;
    bool sweepReload = false;
    bool sweepEnabled = false;
    bool sweepNegate = false;
    uint8_t sweepShift = 0;
    uint8_t sweepPeriod = 0;
    uint8_t sweepValue = 0;

    void sweep()
    {
        const uint16_t delta = timerPeriod >> sweepShift;
        if (sweepNegate)
        {
            // Pulse 1 negates with one's complement
            timerPeriod -= delta + (channel == 1 ? 1 : 0);
        }
        else
        {
            timerPeriod += delta;
        }
    }
};

/**
 * Triangle waveform generator.
 */
class Triangle
{
public:
    bool enabled = false;
    LengthCounter length;

    void writeControl(uint8_t value)
    {
        length.enabled = ((value >> 7) & 1) == 0;
        counterPeriod = value & 0x7f;
    }

    void writeTimerLow(uint8_t value)
    {
        timerPeriod = (timerPeriod & 0xff00) | value;
    }

    void writeTimerHigh(uint8_t value)
    {
        length.load(value);
        timerPeriod = (timerPeriod & 0x00ff) | ((value & 7) << 8);
        timerValue = timerPeriod;
        counterReload = true;
    }

    void stepTimer()
    {
        if (timerValue == 0)
        {
            timerValue = timerPeriod;
            if (length.value > 0 && counterValue > 0)
            {
                dutyValue = (dutyValue + 1) % 32;
            }
        }
        else
        {
            timerValue--;
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
        if (length.enabled)
        {
            counterReload = false;
        }
    }

    uint8_t output() const
    {
        if (!enabled || length.value == 0 || counterValue == 0)
        {
            return 0;
        }
        return triangleTable[dutyValue];
    }

private:
    uint16_t timerPeriod = 0;
    uint16_t timerValue = 0;
    uint8_t dutyValue = 0;
    uint8_t counterPeriod = 0;
    uint8_t counterValue = 0;
    bool counterReload = false;
};

/**
 * Pseudo-random noise generator.
 */
class Noise
{
public:
    bool enabled = false;
    LengthCounter length;

    void writeControl(uint8_t value)
    {
        length.enabled = ((value >> 5) & 1) == 0;
        envelope.writeControl(value);
    }

    void writePeriod(uint8_t value)
    {
        mode = (value & 0x80) == 0x80;
        timerPeriod = noiseTable[value & 0x0f];
    }

    void writeLength(uint8_t value)
    {
        length.load(value);
        envelope.start = true;
    }

    void stepTimer()
    {
        if (timerValue == 0)
        {
            timerValue = timerPeriod;
            const uint16_t feedback = (shiftRegister & 1) ^ ((shiftRegister >> (mode ? 6 : 1)) & 1);
            shiftRegister = static_cast<uint16_t>((shiftRegister >> 1) | (feedback << 14));
        }
        else
        {
            timerValue--;
        }
    }

    void stepEnvelope()
    {
        envelope.step();
    }

    uint8_t output() const
    {
        if (!enabled || length.value == 0 || (shiftRegister & 1) == 1)
        {
            return 0;
        }
        return envelope.output();
    }

private:
    Envelope envelope;
    bool mode = false;
    uint16_t shiftRegister = 1;
    uint16_t timerPeriod = 0;
    uint16_t timerValue = 0;
};

APU::APU(int sampleRate, int frameRate) :
    sampleRate(sampleRate),
    frameRate(frameRate),
    pulse1(std::make_unique<Pulse>(1)),
    pulse2(std::make_unique<Pulse>(2)),
    triangle(std::make_unique<Triangle>()),
    noise(std::make_unique<Noise>()),
    filter(std::make_unique<OutputFilter>(sampleRate))
{
}

APU::~APU() = default;

const std::vector<int16_t>& APU::getSamples() const
{
    return samples;
}

int APU::getOutput() const
{
    return mixer.pulse[pulse1->output() + pulse2->output()] +
           mixer.tnd[3 * triangle->output() + 2 * noise->output()];
}

void APU::stepFrame()
{
    samples.clear();

    // Step the frame counter 4 times per frame, for 240Hz
    for (int quarter = 0; quarter < 4; quarter++)
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

        // Split the frame's samples (e.g. 800 at 48 kHz and 60 fps) across its quarters,
        // with the remainder going to the last quarter
        const int samplesPerFrame = sampleRate / frameRate;
        const int samplesPerQuarter = sampleRate / (frameRate * 4);
        const int64_t samplesToWrite = (quarter == 3) ? samplesPerFrame - 3 * samplesPerQuarter : samplesPerQuarter;

        // Each sample is the average output over the timer steps it covers (a box filter),
        // which suppresses the aliasing of simply picking one step per sample
        int64_t sum = 0;
        int count = 0;
        int average = 0;
        int64_t written = 0;
        for (int64_t step = 1; step <= STEPS_PER_QUARTER_FRAME; step++)
        {
            pulse1->stepTimer();
            pulse2->stepTimer();
            noise->stepTimer();
            triangle->stepTimer();
            triangle->stepTimer();

            sum += getOutput();
            count++;

            while (written < samplesToWrite && step * samplesToWrite >= (written + 1) * STEPS_PER_QUARTER_FRAME)
            {
                if (count > 0)
                {
                    average = static_cast<int>(sum / count);
                    sum = 0;
                    count = 0;
                }
                samples.push_back(filter->process(average));
                written++;
            }
        }
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
    pulse1->length.step();
    pulse2->length.step();
    triangle->length.step();
    noise->length.step();
}

void APU::writeControl(uint8_t value)
{
    pulse1->enabled = (value & 1) == 1;
    pulse2->enabled = (value & 2) == 2;
    triangle->enabled = (value & 4) == 4;
    noise->enabled = (value & 8) == 8;

    // Disabling a channel silences it immediately
    if (!pulse1->enabled)
    {
        pulse1->length.value = 0;
    }
    if (!pulse2->enabled)
    {
        pulse2->length.value = 0;
    }
    if (!triangle->enabled)
    {
        triangle->length.value = 0;
    }
    if (!noise->enabled)
    {
        noise->length.value = 0;
    }
}

void APU::writeRegister(uint16_t address, uint8_t value)
{
    switch (address)
    {
    case 0x4000: pulse1->writeControl(value); break;
    case 0x4001: pulse1->writeSweep(value); break;
    case 0x4002: pulse1->writeTimerLow(value); break;
    case 0x4003: pulse1->writeTimerHigh(value); break;
    case 0x4004: pulse2->writeControl(value); break;
    case 0x4005: pulse2->writeSweep(value); break;
    case 0x4006: pulse2->writeTimerLow(value); break;
    case 0x4007: pulse2->writeTimerHigh(value); break;
    case 0x4008: triangle->writeControl(value); break;
    case 0x400a: triangle->writeTimerLow(value); break;
    case 0x400b: triangle->writeTimerHigh(value); break;
    case 0x400c: noise->writeControl(value); break;
    case 0x400d:
    case 0x400e: noise->writePeriod(value); break;
    case 0x400f: noise->writeLength(value); break;
    case 0x4015: writeControl(value); break;
    case 0x4017:
        // Writing the frame counter immediately clocks all units
        stepEnvelope();
        stepSweep();
        stepLength();
        break;
    default:
        break;
    }
}
