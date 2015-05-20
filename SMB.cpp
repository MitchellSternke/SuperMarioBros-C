#include <cstdio>

#include "SMB.hpp"

/*
 * Macros
 */

/// Macro for creating a memory address variable
#define BIND( func, address ) SMB_TranslationTable[address] = func
#define MEMORY( name, address ) static MemoryAccess name(address)

/*
 * Static variables
 */

SMB_Function SMB_TranslationTable[65536];

/*
 * Memory Address Locations
 */

MEMORY( Sprite_Y_Position, 0x0200 );

/*
 * Functions
 */

static void InitializeMemory();
static void MoveAllSpritesOffscreen();
static void MoveSpritesOffscreen();
static void MoveSpritesOffscreenRoutine(byte);

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

void MoveAllSpritesOffscreen()
{
	// Move all sprites offscreen
	MoveSpritesOffscreenRoutine(0);
}

void MoveSpritesOffscreen()
{
	// Move all but sprite 0 offscreen
	MoveSpritesOffscreenRoutine(4);
}

void MoveSpritesOffscreenRoutine( byte start )
{
	// Set the y value of sprites to 248
	byte i = start;
	do
	{
		Sprite_Y_Position[i] = 0xf8;
		i += 4; // Each entry is stored 4 bytes apart
	}
	while( i != 0 );
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
	BIND( InitializeMemory,        0x90cc );
	BIND( MoveAllSpritesOffscreen, 0x8220 );
	BIND( MoveSpritesOffscreen,    0x8223 );
}
