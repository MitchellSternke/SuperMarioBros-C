/**
 * @file
 * @brief Picture Processing Unit emulation.
 */
#ifndef PPU_HPP
#define PPU_HPP

#include <array>
#include <cstdint>

#include "Palette.hpp"

/**
 * Emulates the NES Picture Processing Unit closely enough for Super Mario Bros.,
 * rendering a whole frame at once rather than per scanline.
 */
class PPU
{
public:
    /**
     * @param chr the 8 KiB of pattern table (CHR) data from the ROM.
     */
    explicit PPU(const uint8_t* chr);

    uint8_t readRegister(uint16_t address);

    void writeRegister(uint16_t address, uint8_t value);

    /**
     * Copy a 256-byte page of memory to sprite memory (OAM DMA).
     */
    void writeDMA(const uint8_t* page);

    /**
     * Render the current frame.
     *
     * @param buffer a 256x240 buffer of ARGB pixels.
     * @param colors the RGB colors of the master palette.
     */
    void render(uint32_t* buffer, const Palette& colors) const;

private:
    const uint8_t* chr;

    uint8_t ppuCtrl = 0;     /**< $2000 */
    uint8_t ppuMask = 0;     /**< $2001 */
    uint8_t oamAddress = 0;  /**< $2003 */
    uint8_t ppuScrollX = 0;  /**< $2005 (the game never scrolls vertically) */

    std::array<uint8_t, 32> paletteRam{}; /**< Palette indices for the background and sprites. */
    std::array<uint8_t, 2048> nametable{}; /**< Background tiles and attributes. */
    std::array<uint8_t, 256> oam{};        /**< Sprite memory. */

    uint16_t currentAddress = 0; /**< Address of the next PPUDATA access. */
    bool writeToggle = false;    /**< Selects which half of PPUSCROLL/PPUADDR the next write sets. */
    uint8_t vramBuffer = 0;      /**< PPUDATA reads are delayed by one byte. */
    bool vblankToggle = false;   /**< PPUSTATUS alternates so the game's polling loops terminate. */

    uint8_t getAttributeTableValue(uint16_t nametableAddress) const;
    uint8_t readByte(uint16_t address) const;
    void writeByte(uint16_t address, uint8_t value);
    void advanceAddress();

    void drawTile(uint32_t* buffer, const Palette& colors, int tile, int paletteOffset,
                  int x, int y, bool flipX = false, bool flipY = false, bool coinHole = false) const;
    void renderBackground(uint32_t* buffer, const Palette& colors) const;
    void renderSprite(uint32_t* buffer, const Palette& colors, int index, bool coinHole) const;
};

#endif // PPU_HPP
