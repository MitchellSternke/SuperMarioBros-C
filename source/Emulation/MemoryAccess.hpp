/**
 * @file
 * @brief 6502 status flags and the memory/register wrapper used by the translated code.
 */
#ifndef MEMORYACCESS_HPP
#define MEMORYACCESS_HPP

#include <cstdint>

/**
 * The 6502 status flags that the translated code depends on.
 */
struct StatusFlags
{
    bool c = false; /**< Carry flag. */
    bool z = false; /**< Zero flag. */
    bool n = false; /**< Negative flag. */

    /**
     * Set the zero and negative flags based on a result value.
     */
    void setZN(uint8_t value)
    {
        z = (value == 0);
        n = (value & 0x80) != 0;
    }
};

/**
 * A byte of emulated memory or a CPU register. Arithmetic and assignment update the status
 * flags exactly like the equivalent 6502 instructions, so the translated code can branch on them.
 *
 * Locations without backing storage (such as hardware registers) are wrapped by value, so
 * modifying them has no effect on the emulated machine.
 */
class MemoryAccess
{
public:
    /**
     * Wrap a location in memory.
     */
    MemoryAccess(StatusFlags& flags, uint8_t* location) :
        flags(flags),
        location(location)
    {
    }

    /**
     * Wrap a value that has no backing storage.
     */
    MemoryAccess(StatusFlags& flags, uint8_t value) :
        flags(flags),
        value(value)
    {
    }

    MemoryAccess(const MemoryAccess&) = default;

    operator uint8_t() const
    {
        return location != nullptr ? *location : value;
    }

    /**
     * Load (LDA, LDX, LDY and transfers between registers).
     */
    MemoryAccess& operator=(uint8_t newValue)
    {
        return store(newValue);
    }

    MemoryAccess& operator=(const MemoryAccess& rhs)
    {
        return store(rhs);
    }

    /**
     * Add with carry (ADC).
     */
    MemoryAccess& operator+=(uint8_t operand)
    {
        const int result = *this + operand + (flags.c ? 1 : 0);
        flags.c = result > 0xff;
        return store(static_cast<uint8_t>(result));
    }

    /**
     * Subtract with borrow (SBC).
     */
    MemoryAccess& operator-=(uint8_t operand)
    {
        const int result = *this - operand - (flags.c ? 0 : 1);
        flags.c = result >= 0;
        return store(static_cast<uint8_t>(result));
    }

    MemoryAccess& operator++()
    {
        return store(static_cast<uint8_t>(*this + 1));
    }

    MemoryAccess& operator--()
    {
        return store(static_cast<uint8_t>(*this - 1));
    }

    MemoryAccess& operator&=(uint8_t operand)
    {
        return store(*this & operand);
    }

    MemoryAccess& operator|=(uint8_t operand)
    {
        return store(*this | operand);
    }

    MemoryAccess& operator^=(uint8_t operand)
    {
        return store(*this ^ operand);
    }

    /**
     * Arithmetic shift left (ASL), one bit per shift.
     */
    MemoryAccess& operator<<=(int shift)
    {
        for (int i = 0; i < shift; i++)
        {
            flags.c = (*this & 0x80) != 0;
            store(static_cast<uint8_t>(*this << 1));
        }
        return *this;
    }

    /**
     * Logical shift right (LSR), one bit per shift.
     */
    MemoryAccess& operator>>=(int shift)
    {
        for (int i = 0; i < shift; i++)
        {
            flags.c = (*this & 0x01) != 0;
            store(static_cast<uint8_t>(*this >> 1));
        }
        return *this;
    }

    /**
     * Rotate left through carry (ROL).
     */
    void rol()
    {
        const bool carry = (*this & 0x80) != 0;
        store(static_cast<uint8_t>((*this << 1) | (flags.c ? 0x01 : 0)));
        flags.c = carry;
    }

    /**
     * Rotate right through carry (ROR).
     */
    void ror()
    {
        const bool carry = (*this & 0x01) != 0;
        store(static_cast<uint8_t>((*this >> 1) | (flags.c ? 0x80 : 0)));
        flags.c = carry;
    }

private:
    StatusFlags& flags;
    uint8_t* location = nullptr;
    uint8_t value = 0;

    MemoryAccess& store(uint8_t newValue)
    {
        (location != nullptr ? *location : value) = newValue;
        flags.setZN(newValue);
        return *this;
    }
};

#endif // MEMORYACCESS_HPP
