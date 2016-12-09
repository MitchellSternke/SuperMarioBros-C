#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <cstdint>

/**
 * Buttons found on a standard controller.
 */
enum ControllerButton
{
    BUTTON_A      = 0,
    BUTTON_B      = 1,
    BUTTON_SELECT = 2,
    BUTTON_START  = 3,
    BUTTON_UP     = 4,
    BUTTON_DOWN   = 5,
    BUTTON_LEFT   = 6,
    BUTTON_RIGHT  = 7
};

/**
 * Emulates an NES game controller device.
 */
class Controller
{
public:
    Controller();

    /**
     * Read from the controller register.
     */
    uint8_t readByte();

    /**
     * Set the state of a button on the controller.
     */
    void setButtonState( ControllerButton button, bool state );

    /**
     * Write a byte to the controller register.
     */
    void writeByte( uint8_t value );

private:
    bool    buttonStates[8];
    uint8_t buttonIndex;
    uint8_t strobe;
};

#endif // CONTROLLER_HPP
