/**
 * @file
 * @brief Window and video output.
 */
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <cstdint>
#include <vector>

#include "Sdl.hpp"

struct Configuration;

/**
 * The game window. Scales the picture to fit while keeping its aspect ratio, optionally
 * with a CRT effect, and draws the pause screen.
 */
class Display
{
public:
    /**
     * @param config video settings.
     * @param chr the game's CHR data, used for the window icon and the pause screen's text.
     * @throws SdlError if the window cannot be created.
     */
    Display(const Configuration& config, const uint8_t* chr);

    /**
     * Show a frame.
     *
     * @param frame 256x240 ARGB pixels.
     * @param paused whether to dim the frame and show the pause screen.
     */
    void present(const uint32_t* frame, bool paused);

    void toggleCrtEffect();
    void toggleFullscreen();

private:
    const uint8_t* chr;
    bool integerScaling;
    bool crtEffect;

    SdlPtr<SDL_Window> window;
    SdlPtr<SDL_Renderer> renderer;
    SdlPtr<SDL_Texture> frameTexture;   /**< The frame at its native resolution. */
    SdlPtr<SDL_Texture> scaledTexture;  /**< The frame enlarged by a whole number (for smooth scaling). */
    SdlPtr<SDL_Texture> crtTexture;     /**< Scanline and phosphor mask, at the output resolution. */
    int scaledFactor = 0;
    SDL_Rect crtRect{};
    std::vector<uint32_t> pauseFrame;

    SDL_Rect getOutputRect() const;
    void drawFrame(const SDL_Rect& outputRect);
    void drawCrtEffect(const SDL_Rect& outputRect);
    void drawText(int y, const char* text, uint32_t color);
};

#endif // DISPLAY_HPP
