/**
 * @file
 * @brief NES controller emulation.
 */
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <cstdint>

/**
 * Buttons of a standard controller, in the order the hardware reports them.
 */
enum class Button : uint8_t
{
    A,
    B,
    Select,
    Start,
    Up,
    Down,
    Left,
    Right
};

/**
 * Emulates an NES game controller: a shift register that reports one button per read.
 */
class Controller
{
public:
    /**
     * Set whether a button is held down.
     */
    void setButtonState(Button button, bool pressed);

    /**
     * Read the controller register ($4016/$4017).
     */
    uint8_t readByte();

    /**
     * Write the strobe register ($4016).
     */
    void writeByte(uint8_t value);

private:
    uint8_t buttonStates = 0; /**< One bit per button. */
    uint8_t buttonIndex = 0;  /**< Next button reported by a read. */
    uint8_t strobe = 1;
};

#endif // CONTROLLER_HPP
