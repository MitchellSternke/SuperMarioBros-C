#include "../SMB/SMBEngine.hpp"

#include "MemoryAccess.hpp"

MemoryAccess::MemoryAccess(SMBEngine& engine, uint8_t* value) :
    engine(engine)
{
    this->value = value;
}

MemoryAccess::MemoryAccess(SMBEngine& engine, uint8_t constant) :
    engine(engine)
{
    this->constant = constant;
    this->value = &constant;
}

MemoryAccess& MemoryAccess::operator = (uint8_t value)
{
    *(this->value) = value;
    engine.setZN(value);
    return *this;
}

MemoryAccess& MemoryAccess::operator = (const MemoryAccess& rhs)
{
    return ((*this) = *(rhs.value));
}

MemoryAccess& MemoryAccess::operator += (uint8_t value)
{
    uint16_t temp = *(this->value) + value + (engine.c ? 1 : 0);
    *(this->value) = temp & 0xff;
    engine.setZN(*(this->value));
    engine.c = temp > 0xff;
    return *this;
}

MemoryAccess& MemoryAccess::operator -= (uint8_t value)
{
    uint16_t temp = *(this->value) - value - (engine.c ? 0 : 1);
    *(this->value) = (temp & 0xff);
    engine.setZN(*(this->value));
    engine.c = temp < 0x100;
    return *this;
}

MemoryAccess& MemoryAccess::operator ++ ()
{
    *(this->value) = *(this->value) + 1;
    engine.setZN(*(this->value));
    return *this;
}

MemoryAccess& MemoryAccess::operator -- ()
{
    *(this->value) = *(this->value) - 1;
    engine.setZN(*(this->value));
    return *this;
}

MemoryAccess& MemoryAccess::operator ++ (int unused)
{
    return ++(*this);
}

MemoryAccess& MemoryAccess::operator -- (int unused)
{
    return --(*this);
}

MemoryAccess& MemoryAccess::operator &= (uint8_t value)
{
    *(this->value) &= value;
    engine.setZN(*(this->value));
    return *this;
}

MemoryAccess& MemoryAccess::operator |= (uint8_t value)
{
    *(this->value) |= value;
    engine.setZN(*(this->value));
    return *this;
}

MemoryAccess& MemoryAccess::operator ^= (uint8_t value)
{
    *(this->value) ^= value;
    engine.setZN(*(this->value));
    return *this;
}

MemoryAccess& MemoryAccess::operator <<= (int shift)
{
    for (int i = 0; i < shift; i++)
    {
        engine.c = *(this->value) & (1 << 7);
        *(this->value) = (*(this->value) << 1) & 0xfe;
        engine.setZN(*(this->value));
    }
    return *this;
}

MemoryAccess& MemoryAccess::operator >>= (int shift)
{
    for (int i = 0; i < shift; i++)
    {
        engine.c = *(this->value) & (1 << 0);
        *(this->value) = (*(this->value) >> 1) & 0x7f;
        engine.setZN(*(this->value));
    }
    return *this;
}

MemoryAccess::operator uint8_t()
{
    return *value;
}

void MemoryAccess::rol()
{
    bool bit7 = *(this->value) & (1 << 7);
    *(this->value) <<= 1;
    if( engine.c )
    {
        *(this->value) |= (1 << 0);
    }
    engine.c = bit7;
    engine.setZN(*(this->value));
}

void MemoryAccess::ror()
{
    bool bit0 = *(this->value) & (1 << 0);
    *(this->value) >>= 1;
    if( engine.c )
    {
        *(this->value) |= (1 << 7);
    }
    engine.c = bit0;
    engine.setZN(*(this->value));
}
