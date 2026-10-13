/**
 * @file
 * @brief The NES master palette.
 */
#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <array>
#include <cstdint>
#include <optional>
#include <string>

/**
 * RGB colors (0xRRGGBB) of the 64 entries of the NES master palette.
 */
using Palette = std::array<uint32_t, 64>;

/**
 * The built-in palette.
 */
extern const Palette DEFAULT_PALETTE;

/**
 * Load a palette from a .pal file: 64 (R,G,B) byte triples. 1536-byte files with emphasis
 * variants are accepted too; only their first 64 colors are used.
 *
 * @return the palette, or nothing if the file could not be loaded (the reason is logged).
 */
std::optional<Palette> loadPalette(const std::string& fileName);

#endif // PALETTE_HPP
