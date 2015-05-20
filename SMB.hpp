#ifndef SMB_HPP
#define SMB_HPP

#include "nesemu1.hh"
#include "Types.hpp"

/**
 * Abstraction for interfacing with memory addresses.
 */
class MemoryAccess
{
public:
	MemoryAccess( int address )
	{
		this->address = address;
	}

	bool operator == ( byte value ) const
	{
		return ((byte)(*this) == value);
	}

	bool operator != ( byte value ) const
	{
		return !(*this == value);
	}

	MemoryAccess& operator = ( byte value )
	{
		writeMemory(address, value);
		return *this;
	}

	MemoryAccess operator [] ( int index )
	{
		return MemoryAccess(address + index);
	}

	MemoryAccess& operator++()
	{
		writeMemory(address, readMemory(address) + 1);
		return *this;
	}

	MemoryAccess& operator++(int)
	{
		++(*this);
		return *this;
	}

	MemoryAccess& operator--()
	{
		writeMemory(address, readMemory(address) - 1);
		return *this;
	}

	MemoryAccess& operator--(int)
	{
		--(*this);
		return *this;
	}

	operator byte() const
	{
		return readMemory(address);
	}

private:
	int address;
};

/// Type for SMB C++ translated functions
typedef void(*SMB_Function)(void);

/// Translated functions are called from this table on each instruction fetch
extern SMB_Function SMB_TranslationTable[65536];

/*
 * Public functions
 */

/**
 * Initialize Super Mario Bros.
 */
void SMB_Init();

#endif // SMB_HPP
