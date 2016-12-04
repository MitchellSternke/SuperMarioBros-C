#include "APU.hpp"
#include "PPU.hpp"
#include "Util.hpp"

#include <cstring>

/**
 * Offset for the first address that corresponds to constant data.
 */
#define DATA_STORAGE_OFFSET 0x8000

/**
 * 32kb (0x8000) bytes of storage to map the NES address space for constants.
 */
static uint8_t dataStorage[0x8000];

/**
 * 2kb of RAM.
 */
static uint8_t ram[0x800];

/**
 * PPU emulator.
 */
static PPU ppu;

/**
 * APU emulator.
 */
static APU apu;

// Controller emulators
Controller controller1;
Controller controller2;

// Return stack management:
static int returnIndexStack[100];
static int returnIndexStackTop = 0;

// NES Registers:
static uint8_t registerA;
static uint8_t registerX;
static uint8_t registerY;
static uint8_t registerS;

void setZN(uint8_t value)
{
    z = (value == 0);
    n = (value & (1 << 7)) != 0;
}

/**
 * Get a pointer to a byte in the address space.
 */
uint8_t* getDataPointer(uint16_t address)
{
    // Constant data
    if( address >= DATA_STORAGE_OFFSET )
    {
        return dataStorage + (address - DATA_STORAGE_OFFSET);
    }
    // RAM and Mirrors
    else if( address < 0x2000 )
    {
        return ram + (address & 0x7ff);
    }

    return nullptr;
}

// Public variables:
bool c;
bool z;
bool n;
MemoryAccess a(&registerA);
MemoryAccess x(&registerX);
MemoryAccess y(&registerY);
MemoryAccess s(&registerS);

// Public Functions:

void compare(uint8_t value1, uint8_t value2)
{
    uint8_t result = value1 - value2;
    c = (value1 >= value2);
    setZN(result);
}

void bit(uint8_t value)
{
    n = (value & (1 << 7)) != 0;
    z = (registerA & value) == 0;
}

void pha()
{
    writeData(0x100 | (uint16_t)registerS, registerA);
    registerS--;
}

void pla()
{
    registerS++;
    a = readData(0x100 | (uint16_t)registerS);
}

int popReturnIndex()
{
    return returnIndexStack[returnIndexStackTop--];
}

void pushReturnIndex(int index)
{
    returnIndexStack[++returnIndexStackTop] = index;
}

uint8_t readData(uint16_t address)
{
    // Constant data
    if( address >= DATA_STORAGE_OFFSET )
    {
        return dataStorage[address - DATA_STORAGE_OFFSET];
    }
    // RAM and Mirrors
    else if( address < 0x2000 )
    {
        return ram[address & 0x7ff];
    }
    // PPU Registers and Mirrors
    else if( address < 0x4000 )
    {
        return ppu.readRegister(0x2000 + (address & 0x7));
    }
    // IO registers
    else if( address < 0x4020 )
    {
        switch (address)
        {
        case 0x4016:
            return controller1.readByte();
        case 0x4017:
            return controller2.readByte();
        }
    }

    return 0;
}

void writeData(uint16_t address, uint8_t value)
{
    // RAM and Mirrors
    if( address < 0x2000 )
    {
        ram[address & 0x7ff] = value;
    }
    // PPU Registers and Mirrors
    else if( address < 0x4000 )
    {
        ppu.writeRegister(0x2000 + (address & 0x7), value);
    }
    // IO registers
    else if( address < 0x4020 )
    {
        switch( address )
        {
        case 0x4014:
            ppu.writeDMA(value);
            break;
        case 0x4016:
            controller1.writeByte(value);
            controller2.writeByte(value);
            break;
        default:
            apu.writeRegister(address, value);
            break;
        }
    }
}

void writeData(uint16_t address, const uint8_t* data, size_t length)
{
    address -= DATA_STORAGE_OFFSET;

    memcpy(dataStorage + (ptrdiff_t)address, data, length);
}

MemoryAccess getMemory(uint16_t address)
{
    uint8_t* dataPointer = getDataPointer(address);
    if( dataPointer != nullptr )
    {
        return MemoryAccess(dataPointer);
    }
    else
    {
        return MemoryAccess(readData(address));
    }
}

uint16_t getMemoryWord(uint8_t address)
{
    return (uint16_t)readData(address) + ((uint16_t)(readData(address + 1)) << 8);
}

uint32_t* render()
{
    apu.stepFrame();
    return ppu.render();
}

void audioCallback(void* userdata, uint8_t* stream, int len)
{
    // Fill the audio buffer with samples from the APU
    apu.output(stream, len);
}
