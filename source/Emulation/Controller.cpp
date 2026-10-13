#include "Controller.hpp"

void Controller::setButtonState(Button button, bool pressed)
{
    const uint8_t mask = static_cast<uint8_t>(1 << static_cast<int>(button));
    buttonStates = pressed ? (buttonStates | mask) : (buttonStates & ~mask);
}

uint8_t Controller::readByte()
{
    // After all eight buttons have been read, the hardware reports 1
    //
    if (buttonIndex >= 8)
    {
        return 1;
    }

    const uint8_t value = ((buttonStates >> buttonIndex) & 1) ? 0x41 : 0x40;
    if ((strobe & 1) == 0)
    {
        buttonIndex++;
    }
    return value;
}

void Controller::writeByte(uint8_t value)
{
    // The shift register reloads when the strobe goes low
    //
    if ((value & 1) == 0 && (strobe & 1) == 1)
    {
        buttonIndex = 0;
    }
    strobe = value;
}
