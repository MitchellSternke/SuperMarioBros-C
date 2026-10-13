#include "../Constants.hpp"

#include "PPU.hpp"

namespace
{

constexpr uint32_t OPAQUE = 0xff000000;

/**
 * Super Mario Bros. uses vertical mirroring: $2000/$2800 share the first kilobyte of nametable
 * memory, and $2400/$2C00 the second.
 */
constexpr uint16_t getNametableIndex(uint16_t address)
{
    return address & 0x07ff;
}

} // namespace

PPU::PPU(const uint8_t* chr) :
    chr(chr)
{
}

uint8_t PPU::getAttributeTableValue(uint16_t nametableAddress) const
{
    nametableAddress = getNametableIndex(nametableAddress);

    // Determine the 32x32 attribute table address
    const int row = ((nametableAddress & 0x3e0) >> 5) / 4;
    const int col = (nametableAddress & 0x1f) / 4;

    // Determine the 16x16 metatile for the 8x8 tile addressed
    const int shift = ((nametableAddress & (1 << 6)) ? 4 : 0) + ((nametableAddress & (1 << 1)) ? 2 : 0);

    // Determine the offset into the attribute table
    const int offset = (nametableAddress & 0xc00) + 0x400 - 64 + (row * 8 + col);

    return (nametable[offset] >> shift) & 0x3;
}

uint8_t PPU::readByte(uint16_t address) const
{
    // Mirror all addresses above $3fff
    address &= 0x3fff;

    if (address < 0x2000)
    {
        return chr[address];
    }
    if (address < 0x3f00)
    {
        return nametable[getNametableIndex(address)];
    }
    return 0;
}

void PPU::writeByte(uint16_t address, uint8_t value)
{
    // Mirror all addresses above $3fff
    address &= 0x3fff;

    if (address < 0x2000)
    {
        // CHR is read-only
    }
    else if (address < 0x3f00)
    {
        nametable[getNametableIndex(address)] = value;
    }
    else if (address < 0x3f20)
    {
        paletteRam[address - 0x3f00] = value;

        // Entry 0 of each sprite palette ($3f10/$3f14/$3f18/$3f1c) mirrors the background palettes
        if (address >= 0x3f10 && (address & 0x03) == 0)
        {
            paletteRam[address - 0x3f10] = value;
        }
    }
}

void PPU::advanceAddress()
{
    currentAddress += (ppuCtrl & (1 << 2)) ? 32 : 1;
}

uint8_t PPU::readRegister(uint16_t address)
{
    switch (address)
    {
    case 0x2002: // PPUSTATUS
    {
        writeToggle = false;
        const uint8_t status = vblankToggle ? 0 : 0xc0;
        vblankToggle = !vblankToggle;
        return status;
    }
    case 0x2004: // OAMDATA
        return oam[oamAddress];
    case 0x2007: // PPUDATA
    {
        const uint8_t value = vramBuffer;
        vramBuffer = readByte(currentAddress);
        advanceAddress();
        return value;
    }
    default:
        return 0;
    }
}

void PPU::writeRegister(uint16_t address, uint8_t value)
{
    switch (address)
    {
    case 0x2000: // PPUCTRL
        ppuCtrl = value;
        break;
    case 0x2001: // PPUMASK
        ppuMask = value;
        break;
    case 0x2003: // OAMADDR
        oamAddress = value;
        break;
    case 0x2004: // OAMDATA
        oam[oamAddress++] = value;
        break;
    case 0x2005: // PPUSCROLL
        if (!writeToggle)
        {
            ppuScrollX = value;
        }
        writeToggle = !writeToggle;
        break;
    case 0x2006: // PPUADDR
        if (!writeToggle)
        {
            currentAddress = static_cast<uint16_t>((currentAddress & 0x00ff) | (value << 8));
        }
        else
        {
            currentAddress = static_cast<uint16_t>((currentAddress & 0xff00) | value);
        }
        writeToggle = !writeToggle;
        break;
    case 0x2007: // PPUDATA
        writeByte(currentAddress, value);
        advanceAddress();
        break;
    default:
        break;
    }
}

void PPU::writeDMA(const uint8_t* page)
{
    for (int i = 0; i < 256; i++)
    {
        oam[oamAddress++] = page[i];
    }
}

void PPU::drawTile(uint32_t* buffer, const Palette& colors, int tile, int paletteOffset,
                   int x, int y, bool flipX, bool flipY, bool coinHole) const
{
    const uint8_t* pattern = chr + tile * 16;
    for (int row = 0; row < 8; row++)
    {
        const int yPixel = y + (flipY ? 7 - row : row);
        if (yPixel < 0 || yPixel >= RENDER_HEIGHT)
        {
            continue;
        }

        for (int column = 0; column < 8; column++)
        {
            // Two bit planes give each pixel a 2-bit color; bit 0 is the rightmost pixel
            const int colorIndex = ((pattern[row] >> column) & 1) | (((pattern[row + 8] >> column) & 1) << 1);
            if (colorIndex == 0)
            {
                continue; // Transparent
            }

            const int xPixel = x + (flipX ? column : 7 - column);
            if (xPixel < 0 || xPixel >= RENDER_WIDTH)
            {
                continue;
            }

            // Sprite 0 (tile $ff) forms part of the coin indicator in the status bar,
            // but a few of its pixels must stay hidden behind it
            if (coinHole && row == 5 && column > 3 && column < 6)
            {
                continue;
            }

            buffer[yPixel * RENDER_WIDTH + xPixel] = OPAQUE | colors[paletteRam[paletteOffset + colorIndex]];
        }
    }
}

void PPU::renderBackground(uint32_t* buffer, const Palette& colors) const
{
    const int patternTable = (ppuCtrl & (1 << 4)) ? 256 : 0;
    const auto renderNametableTile = [&](uint16_t address, int x, int y) {
        drawTile(buffer, colors, readByte(address) + patternTable, getAttributeTableValue(address) * 4, x, y);
    };

    // The status bar (the top four rows) does not scroll
    for (int x = 0; x < 32; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            renderNametableTile(static_cast<uint16_t>(0x2000 + 32 * y + x), x * 8, y * 8);
        }
    }

    const int scrollX = ppuScrollX + ((ppuCtrl & (1 << 0)) ? 256 : 0);
    for (int x = scrollX / 8; x <= (scrollX + RENDER_WIDTH) / 8; x++)
    {
        for (int y = 4; y < 30; y++)
        {
            // Columns continue from one nametable into the next
            const uint16_t address = static_cast<uint16_t>(0x2000 + 0x400 * (x / 32) + 32 * y + (x % 32));
            renderNametableTile(address, x * 8 - scrollX, y * 8);
        }
    }
}

void PPU::renderSprite(uint32_t* buffer, const Palette& colors, int index, bool coinHole) const
{
    const uint8_t y = oam[index * 4];
    const uint8_t tile = oam[index * 4 + 1];
    const uint8_t attributes = oam[index * 4 + 2];
    const uint8_t x = oam[index * 4 + 3];

    // Hidden sprites are moved off the bottom of the screen
    if (y >= 0xef || x >= 0xf9)
    {
        return;
    }

    drawTile(buffer, colors,
             tile + ((ppuCtrl & (1 << 3)) ? 256 : 0),
             0x10 + (attributes & 0x03) * 4,
             x,
             y + 1, // Sprite data is delayed by one scanline
             (attributes & (1 << 6)) != 0,
             (attributes & (1 << 7)) != 0,
             coinHole);
}

void PPU::render(uint32_t* buffer, const Palette& colors) const
{
    const uint32_t backgroundColor = OPAQUE | colors[paletteRam[0]];
    for (int i = 0; i < RENDER_WIDTH * RENDER_HEIGHT; i++)
    {
        buffer[i] = backgroundColor;
    }

    const bool spritesEnabled = (ppuMask & (1 << 4)) != 0;
    const bool backgroundEnabled = (ppuMask & (1 << 3)) != 0;
    const auto isBehindBackground = [this](int index) {
        return (oam[index * 4 + 2] & (1 << 5)) != 0;
    };
    const auto isCoinIndicator = [this](int index) {
        return index == 0 && oam[1] == 0xff;
    };

    // Sprites with the lowest index in OAM take priority, so sprites are drawn in reverse order
    if (spritesEnabled)
    {
        for (int i = 63; i >= 0; i--)
        {
            if (isBehindBackground(i))
            {
                renderSprite(buffer, colors, i, false);
            }
        }
    }

    if (backgroundEnabled)
    {
        renderBackground(buffer, colors);
    }

    if (spritesEnabled)
    {
        // Sprite 0 is drawn first as a special case (the coin indicator), then 63 down to 1
        for (int j = 64; j > 0; j--)
        {
            const int i = j % 64;
            if (!isBehindBackground(i) || isCoinIndicator(i))
            {
                renderSprite(buffer, colors, i, isCoinIndicator(i));
            }
        }
    }
}
