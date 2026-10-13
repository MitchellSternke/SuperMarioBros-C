/**
 * @file
 * @brief Ownership of SDL objects.
 */
#ifndef SDL_HPP
#define SDL_HPP

#include <memory>
#include <stdexcept>
#include <string>

#include <SDL.h>

struct SdlDeleter
{
    void operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
    void operator()(SDL_Renderer* renderer) const { SDL_DestroyRenderer(renderer); }
    void operator()(SDL_Texture* texture) const { SDL_DestroyTexture(texture); }
    void operator()(SDL_Surface* surface) const { SDL_FreeSurface(surface); }
    void operator()(SDL_GameController* controller) const { SDL_GameControllerClose(controller); }
};

/**
 * An SDL object that is destroyed when it goes out of scope.
 */
template <typename T>
using SdlPtr = std::unique_ptr<T, SdlDeleter>;

/**
 * An SDL call failed.
 */
class SdlError : public std::runtime_error
{
public:
    explicit SdlError(const std::string& function) :
        std::runtime_error(function + " failed: " + SDL_GetError())
    {
    }
};

#endif // SDL_HPP
