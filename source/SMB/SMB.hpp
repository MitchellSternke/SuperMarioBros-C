/**
 * @file
 * @brief Support definitions for the generated game code (SMB.cpp and SMBData.cpp).
 */
#ifndef SMB_HPP
#define SMB_HPP

#include <cstdint>

#include "SMBEngine.hpp"

/**
 * Low byte of a 16-bit value (the assembler's '<' operator).
 */
constexpr uint8_t lowByte(uint16_t value)
{
    return static_cast<uint8_t>(value & 0xff);
}

/**
 * High byte of a 16-bit value (the assembler's '>' operator).
 */
constexpr uint8_t highByte(uint16_t value)
{
    return static_cast<uint8_t>(value >> 8);
}

#include "SMBConstants.hpp"
#include "SMBDataPointers.hpp"

/**
 * Access a byte of emulated memory.
 */
#define M(addr) getMemory(addr)

/**
 * Read a little-endian word from the zero page.
 */
#define W(addr) getMemoryWord(addr)

/**
 * Call a subroutine stored in a goto label. The index identifies the return point (see the
 * jump table at the end of SMB.cpp).
 */
#define JSR(subroutine, index) pushReturnIndex(index); goto subroutine; Return_ ## index:

#endif // SMB_HPP
