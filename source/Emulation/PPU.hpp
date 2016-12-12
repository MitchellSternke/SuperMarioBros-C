#ifndef PPU_HPP
#define PPU_HPP

#include <cstdint>

class SMBEngine;

/**
 * Emulates the NES Picture Processing Unit.
 */
class PPU
{
public:
    PPU(SMBEngine& engine);

    uint8_t readRegister(uint16_t address);

    /**
     * Render to a frame buffer.
     */
    void render(uint32_t* buffer);

    void writeDMA(uint8_t page);

    void writeRegister(uint16_t address, uint8_t value);

private:
    SMBEngine& engine;

    uint8_t ppuCtrl; /**< $2000 */
    uint8_t ppuMask; /**< $2001 */
    uint8_t ppuStatus; /**< 2002 */
    uint8_t oamAddress; /**< $2003 */
    uint8_t ppuScrollX; /**< $2005 */
    uint8_t ppuScrollY; /**< $2005 */

    uint8_t palette[32]; /**< Palette data. */
    uint8_t nametable[2048]; /**< Background table. */
    uint8_t oam[256]; /**< Sprite memory. */

    // PPU Address control
    uint16_t currentAddress; /**< Address that will be accessed on the next PPU read/write. */
    bool writeToggle; /**< Toggles whether the low or high bit of the current address will be set on the next write to PPUADDR. */
    uint8_t vramBuffer; /**< Stores the last read byte from VRAM to delay reads by 1 byte. */

    uint8_t getAttributeTableValue(uint16_t nametableAddress);
    uint16_t getNametableIndex(uint16_t address);
    uint8_t readByte(uint16_t address);
    uint8_t readCHR(int index);
    uint8_t readDataRegister();
    void renderTile(uint32_t* buffer, int index, int xOffset, int yOffset);
    void writeAddressRegister(uint8_t value);
    void writeByte(uint16_t address, uint8_t value);
    void writeDataRegister(uint8_t value);
};

#endif // PPU_HPP
