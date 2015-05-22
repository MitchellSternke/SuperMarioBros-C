#ifndef NESEMU1_HH
#define NESEMU1_HH

#include "Types.hpp"

// Interface for the NES emulator code

byte readMemory( int address );
void writeMemory( int address, byte value );

byte readA();
byte readX();
byte readY();
void writeA( byte value );
void writeX( byte value );
void writeY( byte value );

#endif // NESEMU1_HH
