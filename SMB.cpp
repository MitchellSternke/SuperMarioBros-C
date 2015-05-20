#include <cstdio>

#include "SMB.hpp"

/*
 * Macros
 */

/// Macro for creating a memory address variable
#define BIND( func, address ) SMB_TranslationTable[address] = func
#define MEMORY( name, address ) MemoryAccess name(address)

/*
 * Static variables
 */

SMB_Function SMB_TranslationTable[65536];

/*
 * Memory Address Locations
 */

/*
 * Functions
 */

void InitializeMemory()
{
	printf("Initializing Memory\n");

	// Clear RAM, skipping the stack
	byte x = 7; // Start on page 7
	byte y = readY(); // TODO: make this a parameter
	do
	{
		do
		{
			// Don't touch the stack ($160-$1ff)
			if( x != 1 || y < 0x60 )
			{
				writeMemory(((word)x << 8) + y, 0);
			}
		}
		while( --y != 0xff );
	}
	while( --x != 0xff );

	writeA(0);
	writeX(x);
	writeY(y);
}

/*
 * Public functions defined in SMB.hpp
 */

void SMB_Init()
{
	// Initialize the translation table
	for( int i = 0; i < 65536; i++ )
	{
		SMB_TranslationTable[i] = nullptr;
	}

	// Function binding points
	BIND( InitializeMemory, 0x90cc );
}
