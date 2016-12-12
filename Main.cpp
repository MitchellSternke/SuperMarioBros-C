#include <cstdio>

#include <SDL2/SDL.h>

#include "Controller.hpp"
#include "SMBEngine.hpp"
#include "Video.hpp"

#define RENDER_WIDTH 256
#define RENDER_HEIGHT 240
#define SCALE 3

#define FREQUENCY 44100

uint8_t* romImage;
static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture* texture;
static SDL_Texture* scanlineTexture;
static SMBEngine* smbEngine = nullptr;
static uint32_t renderBuffer[256 * 240];

/**
 * Load the Super Mario Bros. ROM image.
 */
static bool loadRomImage()
{
    // TODO: this should be configurable
    FILE* file = fopen("Super Mario Bros. (JU) (PRG0) [!].nes", "r");
    if (file == NULL)
    {
        return false;
    }

    // Find the size of the file
    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0L, SEEK_SET);

    // Read the entire file into a buffer
    romImage = new uint8_t[fileSize];
    fread(romImage, sizeof(uint8_t), fileSize, file);
    fclose(file);

    return true;
}

/**
 * Generate a texture for a scanline overlay effect.
 */
static void generateScanlineTexture()
{
    // Create a scanline texture for 3x rendering
    scanlineTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, RENDER_WIDTH * 3, RENDER_HEIGHT * 3);
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
}

/**
 * SDL Audio callback function.
 */
static void audioCallback(void* userdata, uint8_t* buffer, int len)
{
    if (smbEngine != nullptr)
    {
        smbEngine->audioCallback(buffer, len);
    }
}

/**
 * Initialize libraries for use.
 */
static bool initialize()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        return false;
    }

    // Create the window
    window = SDL_CreateWindow("Super Mario Bros.",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              RENDER_WIDTH * SCALE,
                              RENDER_HEIGHT * SCALE,
                              0
    );

    // Setup the renderer and texture buffer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, RENDER_WIDTH, RENDER_HEIGHT);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, RENDER_WIDTH, RENDER_HEIGHT);

    generateScanlineTexture();

    // Initialize audio
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = FREQUENCY;
    desiredSpec.format = AUDIO_S8;
    desiredSpec.channels = 1;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audioCallback;
    desiredSpec.userdata = NULL;

    SDL_AudioSpec obtainedSpec;
    SDL_OpenAudio(&desiredSpec, &obtainedSpec);

    // Start playing audio
    SDL_PauseAudio(0);

    return true;
}

/**
 * Shutdown libraries for exit.
 */
static void shutdown()
{
    SDL_CloseAudio();

    SDL_DestroyTexture(scanlineTexture);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

static void mainLoop()
{
    SMBEngine engine(romImage);
    smbEngine = &engine;
    engine.reset();

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                    running = false;
                    break;
                }
                break;

            default:
                break;
            }
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);
        Controller& controller1 = engine.getController1();
        controller1.setButtonState(BUTTON_A, keys[SDL_SCANCODE_X]);
        controller1.setButtonState(BUTTON_B, keys[SDL_SCANCODE_Z]);
        controller1.setButtonState(BUTTON_SELECT, keys[SDL_SCANCODE_BACKSPACE]);
        controller1.setButtonState(BUTTON_START, keys[SDL_SCANCODE_RETURN]);
        controller1.setButtonState(BUTTON_UP, keys[SDL_SCANCODE_UP]);
        controller1.setButtonState(BUTTON_DOWN, keys[SDL_SCANCODE_DOWN]);
        controller1.setButtonState(BUTTON_LEFT, keys[SDL_SCANCODE_LEFT]);
        controller1.setButtonState(BUTTON_RIGHT, keys[SDL_SCANCODE_RIGHT]);

        if (keys[SDL_SCANCODE_R])
        {
            // Reset
            engine.reset();
        }
        if (keys[SDL_SCANCODE_ESCAPE])
        {
            // quit
            running = false;
            break;
        }

        engine.update();
        engine.render(renderBuffer);

        SDL_UpdateTexture(texture, NULL, renderBuffer, sizeof(uint32_t) * RENDER_WIDTH);

        SDL_RenderClear(renderer);

        // Render the screen
        SDL_RenderSetLogicalSize(renderer, RENDER_WIDTH, RENDER_HEIGHT);
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // Render scanlines
        SDL_RenderSetLogicalSize(renderer, RENDER_WIDTH * 3, RENDER_HEIGHT * 3);
        SDL_RenderCopy(renderer, scanlineTexture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char** argv)
{
    if (!loadRomImage())
    {
        return -1;
    }

    if (!initialize())
    {
        return -1;
    }

    mainLoop();

    shutdown();

    return 0;
}
