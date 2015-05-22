#include <cstdio>

#include "SMB.hpp"

/*
 * Macros
 */

/// Macro for creating a memory address variable
#define BIND( func, address ) SMB_TranslationTable[address] = func
#define MEMORY( name, address ) static MemoryAccess name(address)

/*
 * Constants
 */

#define TitleScreenModeValue (byte)0
#define GameModeValue        (byte)1
#define VictoryModeValue     (byte)2
#define GameOverModeValue    (byte)3

/*
 * Static variables
 */

SMB_Function SMB_TranslationTable[65536];

/*
 * Memory Address Locations
 */

MEMORY( Sprite_Y_Position, 0x0200 );

MEMORY( OperMode, 0x0770 );

MEMORY( DisplayDigits, 0x07d7 );
MEMORY( DigitModifier, 0x0134 );

/*
 * Functions
 */

static void DigitsMathRoutine();
static void InitializeMemory();
static void MoveAllSpritesOffscreen();
static void MoveSpritesOffscreen();
static void MoveSpritesOffscreenRoutine(byte);

/**
 * Adds DigitModifier to DisplayDigits offset by the value stored in Y.
 */
void DigitsMathRoutine()
{
	printf("Doing digits math\n");

	byte y = readY(); // TODO: make this a parameter
	if( OperMode != TitleScreenModeValue )
	{
		for( sbyte x = 5; x >= 0; x-- )
		{
			byte a = DigitModifier[x] + DisplayDigits[y];
			if( (sbyte)a < 0 )
			{
				// Borrow
				(DigitModifier[x - 1])--;
				a = 9;
			}
			else if( a >= 10 )
			{
				// Carry one
				a -= 10;
				(DigitModifier[x - 1])++;
			}

			DisplayDigits[y] = a;
			y--;
		}
	}

	byte a = 0;
	for( sbyte x = 6; x >= 0; x-- )
	{
		DigitModifier[x - 1] = a;
	}
}

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
	BIND( DigitsMathRoutine,       0x8f5f );
	BIND( InitializeMemory,        0x90cc );
	BIND( MoveAllSpritesOffscreen, 0x8220 );
	BIND( MoveSpritesOffscreen,    0x8223 );
}
