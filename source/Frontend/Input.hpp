/**
 * @file
 * @brief Keyboard and gamepad input.
 */
#ifndef INPUT_HPP
#define INPUT_HPP

#include <vector>

#include "Sdl.hpp"

class SMBEngine;

/**
 * Maps the keyboard and gamepads to the NES controllers. The keyboard and the first gamepad
 * control player 1; a second gamepad controls player 2.
 */
class Input
{
public:
    /**
     * Handle gamepads being connected and disconnected.
     */
    void handleEvent(const SDL_Event& event);

    /**
     * Update the state of the engine's controllers.
     */
    void update(SMBEngine& engine) const;

private:
    std::vector<SdlPtr<SDL_GameController>> gamepads;
};

#endif // INPUT_HPP
