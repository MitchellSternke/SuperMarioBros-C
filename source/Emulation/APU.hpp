#ifndef APU_HPP
#define APU_HPP

#include <cstdint>

#define AUDIO_BUFFER_LENGTH 4096

class Pulse;
class Triangle;
class Noise;

/**
 * Audio processing unit emulator.
 */
class APU
{
public:
    APU();
    ~APU();

    /**
     * Step the APU by one frame.
     */
    void stepFrame();

    void output(uint8_t* buffer, int len);

    void writeRegister(uint16_t address, uint8_t value);

private:
    uint8_t audioBuffer[AUDIO_BUFFER_LENGTH];
    int audioBufferLength;

    int frameValue; /**< The value of the frame counter. */

    Pulse* pulse1;
    Pulse* pulse2;
    Triangle* triangle;
    Noise* noise;

    uint8_t getOutput();
    void stepEnvelope();
    void stepSweep();
    void stepLength();
    void writeControl(uint8_t value);
};

#endif // APU_HPP
