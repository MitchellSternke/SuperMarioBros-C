/**
 * @file
 * @brief Defines utility methods that serve to simulate parts of the NES for ease
 * of translation to C++.
 */
#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>

#include <boost/utility/binary.hpp>

#include "Controller.hpp"

// Macros:
#define JSR(subroutine, index) pushReturnIndex(index); goto subroutine; Return_ ## index:
#define HIBYTE(v) ((v >> 8) & 0xff)
#define LOBYTE(v) (v & 0xff)

// NES-related flags:
extern bool c; /**< Carry flag. */
extern bool z; /**< Zero flag. */
extern bool n; /**< Negative flag. */

/**
 * Set the zero and negative flags based on a result value.
 */
void setZN(uint8_t value);

/**
 * Wraps operations to memory values/registers so that status flags can be set for branch operations.
 */
class MemoryAccess
{
public:
    /**
     * Construct a MemoryAccess to a location.
     */
    MemoryAccess(uint8_t* value)
    {
        this->value = value;
    }

    /**
     * Construct a MemoryAccess to a constant value.
     */
    MemoryAccess(uint8_t constant)
    {
        this->constant = constant;
        this->value = &constant;
    }

    inline MemoryAccess& operator = (uint8_t value)
    {
        *(this->value) = value;
        setZN(value);
        return *this;
    }

    inline MemoryAccess& operator = (const MemoryAccess& rhs)
    {
        return ((*this) = *(rhs.value));
    }

    inline MemoryAccess& operator += (uint8_t value)
    {
        uint16_t temp = *(this->value) + value + (c ? 1 : 0);
        *(this->value) = temp & 0xff;
        setZN(*(this->value));
        c = temp > 0xff;
        return *this;
    }

    inline MemoryAccess& operator -= (uint8_t value)
    {
        uint16_t temp = *(this->value) - value - (c ? 0 : 1);
        *(this->value) = (temp & 0xff);
        setZN(*(this->value));
        c = temp < 0x100;
        return *this;
    }

    inline MemoryAccess& operator ++ ()
    {
        *(this->value) = *(this->value) + 1;
        setZN(*(this->value));
        return *this;
    }

    inline MemoryAccess& operator -- ()
    {
        *(this->value) = *(this->value) - 1;
        setZN(*(this->value));
        return *this;
    }

    inline MemoryAccess& operator ++ (int unused)
    {
        return ++(*this);
    }

    inline MemoryAccess& operator -- (int unused)
    {
        return --(*this);
    }

    inline MemoryAccess& operator &= (uint8_t value)
    {
        *(this->value) &= value;
        setZN(*(this->value));
        return *this;
    }

    inline MemoryAccess& operator |= (uint8_t value)
    {
        *(this->value) |= value;
        setZN(*(this->value));
        return *this;
    }

    inline MemoryAccess& operator ^= (uint8_t value)
    {
        *(this->value) ^= value;
        setZN(*(this->value));
        return *this;
    }

    inline MemoryAccess& operator <<= (int shift)
    {
        for (int i = 0; i < shift; i++)
        {
            c = *(this->value) & (1 << 7);
            *(this->value) = (*(this->value) << 1) & 0xfe;
            setZN(*(this->value));
        }
        return *this;
    }

    inline MemoryAccess& operator >>= (int shift)
    {
        for (int i = 0; i < shift; i++)
        {
            c = *(this->value) & (1 << 0);
            *(this->value) = (*(this->value) >> 1) & 0x7f;
            setZN(*(this->value));
        }
        return *this;
    }

    inline operator uint8_t()
    {
        return *value;
    }

    /**
     * Circular left bit rotation.
     */
    inline void rol()
    {
        bool bit7 = *(this->value) & (1 << 7);
        *(this->value) <<= 1;
        if( c )
        {
            *(this->value) |= (1 << 0);
        }
        c = bit7;
        setZN(*(this->value));
    }

    /**
     * Circular right bit rotation.
     */
    inline void ror()
    {
        bool bit0 = *(this->value) & (1 << 0);
        *(this->value) >>= 1;
        if( c )
        {
            *(this->value) |= (1 << 7);
        }
        c = bit0;
        setZN(*(this->value));
    }

private:
    uint8_t* value;
    uint8_t constant;
};

// NES-related registers:
extern MemoryAccess a;
extern MemoryAccess x;
extern MemoryAccess y;
extern MemoryAccess s;

/**
 * Logic for CMP, CPX, CPY instructions.
 */
void compare(uint8_t value1, uint8_t value2);

/**
 * BIT instruction.
 */
void bit(uint8_t value);

/**
 * PHA instruction.
 */
void pha();

/**
 * PLA instruction.
 */
void pla();

/**
 * Pop an index from the return stack.
 */
int popReturnIndex();

/**
 * Push an index to the return stack.
 */
void pushReturnIndex(int index);

/**
 * Read data from an address in the NES address space.
 */
uint8_t readData(uint16_t address);

/**
 * Write data to an address in the NES address space.
 */
void writeData(uint16_t address, uint8_t value);

/**
 * Map constant data to the address space. The address must be at least 0x8000.
 */
void writeData(uint16_t address, const uint8_t* data, size_t length);

/**
 * Get a memory access object for a particular address.
 */
MemoryAccess getMemory(uint16_t address);

/**
 * Get a word of memory from a zero-page address and the next byte (wrapped around),
 * in little-endian format.
 */
uint16_t getMemoryWord(uint8_t address);

#define M(addr) getMemory(addr)

#define W(addr) getMemoryWord(addr)

/**
 * Get CHR data from the ROM.
 */
uint8_t* getChr();

/**
 * Render the screen to a buffer of pixels.
 */
uint32_t* render();

void audioCallback(void* userdata, uint8_t* stream, int len);

extern Controller controller1;
extern Controller controller2;

#endif // UTIL_HPP
