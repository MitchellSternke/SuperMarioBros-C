/**
 * @file
 * @brief defines video utility functions.
 */
#ifndef VIDEO_HPP
#define VIDEO_HPP

#include <cstdint>
#include <string>

#include <SDL2/SDL.h>

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

/**
 * Draw a box.
 */
void drawBox(uint32_t* buffer, int xOffset, int yOffset, int width, int height, uint32_t palette = 0);

/**
 * Draw a tile from CHR memory.
 */
void drawCHRTile(uint32_t* buffer, int xOffset, int yOffset, int tile, uint32_t palette = 0);

/**
 * Draw a string using characters from CHR.
 */
void drawText(uint32_t* buffer, int xOffset, int yOffset, const std::string& text, uint32_t palette = 0);

/**
 * Generate a texture for a scanline overlay effect.
 */
SDL_Texture* generateScanlineTexture(SDL_Renderer* renderer);

/**
 * Load a palette from file.
 */
const uint32_t* loadPalette(const std::string& fileName);

extern const uint32_t* paletteRGB;
extern uint8_t* romImage;

#endif // VIDEO_HPP
