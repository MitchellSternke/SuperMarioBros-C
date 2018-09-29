#include <iostream>

#include "../Constants.hpp"

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

SDL_Texture* generateScanlineTexture(SDL_Renderer* renderer)
{
    // Create a scanline texture for 3x rendering
    SDL_Texture* scanlineTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, RENDER_WIDTH * 3, RENDER_HEIGHT * 3);
    uint32_t* scanlineTextureBuffer = new uint32_t[RENDER_WIDTH * RENDER_HEIGHT * 3 * 3];
    for (int y = 0; y < RENDER_HEIGHT; y++)
    {
        for (int x = 0; x < RENDER_WIDTH; x++)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    uint32_t color = 0xff000000;
                    switch (j)
                    {
                    case 0:
                        color |= 0xfdd6c7;
                        break;
                    case 1:
                        color |= 0xbef5e1;
                        break;
                    case 2:
                        color |= 0xcfe2ff;
                        break;
                    }
                    scanlineTextureBuffer[((y * 3) + i) * (RENDER_WIDTH * 3) + (x * 3) + j] = color;
                }
            }
        }
    }
    SDL_SetTextureBlendMode(scanlineTexture, SDL_BLENDMODE_MOD);
    SDL_UpdateTexture(scanlineTexture, NULL, scanlineTextureBuffer, sizeof(uint32_t) * RENDER_WIDTH * 3);
    delete [] scanlineTextureBuffer;

    return scanlineTexture;
}

const uint32_t* loadPalette(const std::string& fileName)
{
    uint32_t* palette = nullptr;

    FILE* file = fopen(fileName.c_str(), "r");

    if (file != nullptr)
    {
        // Find the size of the file
        //
        fseek(file, 0L, SEEK_END);
        size_t fileSize = ftell(file);
        fseek(file, 0L, SEEK_SET);

        // Read the entire file into a buffer
        //
        uint8_t* fileBuffer = new uint8_t[fileSize];
        fread(fileBuffer, sizeof(uint8_t), fileSize, file);

        // Size determines the type of palette file
        //
        if (fileSize == 192 ||
            fileSize == 1536)
        {
            palette = new uint32_t[64];
            
            for (int entry = 0; entry < 64; entry++)
            {
                palette[entry] = 
                    (static_cast<uint32_t>(fileBuffer[entry * 3]) << 16) |
                    (static_cast<uint32_t>(fileBuffer[entry * 3 + 1]) << 8) |
                    (static_cast<uint32_t>(fileBuffer[entry * 3 + 2]));
            }
        }
        else
        {
            delete [] fileBuffer;
            std::cout << "Unsupported palette file \"" << fileName << "\"" << std::endl;
        }

        fclose(file);
    }
    else
    {
        std::cout << "Unable to open palette file \"" << fileName << "\"" << std::endl;
    }

    return palette;
}
