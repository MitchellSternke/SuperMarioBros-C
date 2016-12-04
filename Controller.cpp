#include "Controller.hpp"

Controller::Controller()
{
    for( auto& b : buttonStates )
    {
        b = false;
    }
    buttonIndex = 0;
    strobe = 1;
}

uint8_t Controller::readByte()
{
    uint8_t value = 1;

    if( buttonIndex < 8 )
    {
        value = (buttonStates[buttonIndex] ? 0x41 : 0x40);
    }

    if( (strobe & (1 << 0)) == 0 )
    {
        buttonIndex++;
    }

    return value;
}

void Controller::setButtonState( ControllerButton button, bool state )
{
    buttonStates[(int)button] = state;
}

void Controller::writeByte( uint8_t value )
{
    if( (value & (1 << 0)) == 0 && (strobe & (1 << 0)) == 1 )
    {
        buttonIndex = 0;
    }
    strobe = value;
}
