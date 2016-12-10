#ifndef MEMORYACCESS_HPP
#define MEMORYACCESS_HPP

#include <cstdint>

class SMBEngine;

/**
 * Wraps operations to memory values/registers so that status flags can be set for branch operations.
 */
class MemoryAccess
{
public:
    /**
     * Construct a MemoryAccess to a location.
     */
    MemoryAccess(SMBEngine& engine, uint8_t* value);

    /**
     * Construct a MemoryAccess to a constant value.
     */
    MemoryAccess(SMBEngine& engine, uint8_t constant);

    MemoryAccess& operator = (uint8_t value);
    MemoryAccess& operator = (const MemoryAccess& rhs);
    MemoryAccess& operator += (uint8_t value);
    MemoryAccess& operator -= (uint8_t value);
    MemoryAccess& operator ++ ();
    MemoryAccess& operator -- ();
    MemoryAccess& operator ++ (int unused);
    MemoryAccess& operator -- (int unused);
    MemoryAccess& operator &= (uint8_t value);
    MemoryAccess& operator |= (uint8_t value);
    MemoryAccess& operator ^= (uint8_t value);
    MemoryAccess& operator <<= (int shift);
    MemoryAccess& operator >>= (int shift);
    operator uint8_t();

    /**
     * Circular left bit rotation.
     */
    void rol();

    /**
     * Circular right bit rotation.
     */
    void ror();

private:
    SMBEngine& engine;
    uint8_t* value;
    uint8_t constant;
};

#endif // MEMORYACCESS_HPP
