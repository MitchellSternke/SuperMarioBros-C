/**
 * @file
 * @brief defines video utility functions.
 */
#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <cstdint>
#include <string>

/**
 * Constants for specific tiles in CHR.
 */
enum Tile
{
    TILE_BOX_NW = 324,
    TILE_BOX_N = 328,
    TILE_BOX_NE = 329,
    TILE_BOX_W = 326,
    TILE_BOX_CENTER = 294,
    TILE_BOX_E = 330,
    TILE_BOX_SW = 351,
    TILE_BOX_S = 376,
    TILE_BOX_SE = 378
};

void drawBox(uint32_t* buffer, int xOffset, int yOffset, int width, int height, uint32_t palette = 0);
void drawCHRTile(uint32_t* buffer, int xOffset, int yOffset, int tile, uint32_t palette = 0);
void drawText(uint32_t* buffer, int xOffset, int yOffset, const std::string& text, uint32_t palette = 0);

extern const uint32_t paletteRGB[64];
extern uint8_t* romImage;

#endif // VIDEO_HPP
