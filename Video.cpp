#include "Video.hpp"

void drawBox(uint32_t* buffer, int xOffset, int yOffset, int width, int height, uint32_t palette)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int tile;
            if (y == 0)
            {
                if (x == 0)
                {
                    tile = TILE_BOX_NW;
                }
                else if (x == width - 1)
                {
                    tile = TILE_BOX_NE;
                }
                else
                {
                    tile = TILE_BOX_N;
                }
            }
            else if (y == height - 1)
            {
                if (x == 0)
                {
                    tile = TILE_BOX_SW;
                }
                else if (x == width - 1)
                {
                    tile = TILE_BOX_SE;
                }
                else
                {
                    tile = TILE_BOX_S;
                }
            }
            else
            {
                if (x == 0)
                {
                    tile = TILE_BOX_W;
                }
                else if (x == width - 1)
                {
                    tile = TILE_BOX_E;
                }
                else
                {
                    tile = TILE_BOX_CENTER;
                }
            }
            drawCHRTile(buffer, xOffset + x * 8, yOffset + y * 8, tile, palette);
        }
    }
}

void drawCHRTile(uint32_t* buffer, int xOffset, int yOffset, int tile, uint32_t palette)
{
    // Read the pixels of the tile
    for( int row = 0; row < 8; row++ )
    {
        uint8_t plane1 = romImage[16 + 2 * 16384 + tile * 16 + row];
        uint8_t plane2 = romImage[16 + 2 * 16384 + tile * 16 + row + 8];

        for( int column = 0; column < 8; column++ )
        {
            uint8_t paletteIndex = (((plane1 & (1 << column)) ? 1 : 0) + ((plane2 & (1 << column)) ? 2 : 0));
            if( paletteIndex == 0 )
            {
                // skip transparent pixels
                continue;
            }
            uint32_t pixel;
            if (palette == 0)
            {
                // Grayscale
                pixel = 0xff000000 | (paletteIndex * 0x555555);
            }
            else
            {
                uint32_t colorIndex = (palette >> (8 * (3 - paletteIndex))) & 0xff;
                pixel = 0xff000000 | paletteRGB[colorIndex];
            }

            int x = (xOffset + (7 - column));
            int y = (yOffset + row);
            if (x < 0 || x >= 256 || y < 0 || y >= 240)
            {
                continue;
            }
            buffer[y * 256 + x] = pixel;
        }
    }
}

void drawText(uint32_t* buffer, int xOffset, int yOffset, const std::string& text, uint32_t palette)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        int tile = 256 + 36; // SPACE
        char c = text[i];
        if (c >= '0' && c <= '9')
        {
            tile = 256 + (int)(c - '0');
        }
        else if (c >= 'a' && c <= 'z')
        {
            tile = 256 + 10 + (int)(c - 'a');
        }
        else if (c >= 'A' && c <= 'Z')
        {
            tile = 256 + 10 + (int)(c - 'A');
        }
        else if (c == '-')
        {
            tile = 256 + 40;
        }
        else if (c == '!')
        {
            tile = 256 + 43;
        }
        else if (c == '*')
        {
            tile = 256 + 41;
        }
        else if (c == '$')
        {
            tile = 256 + 46;
        }
        drawCHRTile(buffer, xOffset + i * 8, yOffset, tile, palette);
    }
}
