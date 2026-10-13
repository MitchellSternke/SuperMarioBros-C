#include <algorithm>
#include <array>
#include <iostream>

#include "../SMB/SMBEngine.hpp"

#include "Input.hpp"

namespace
{

struct KeyBinding
{
    SDL_Scancode key;
    Button button;
};

const KeyBinding KEY_BINDINGS[] = {
    {SDL_SCANCODE_X, Button::A},
    {SDL_SCANCODE_Z, Button::B},
    {SDL_SCANCODE_BACKSPACE, Button::Select},
    {SDL_SCANCODE_RETURN, Button::Start},
    {SDL_SCANCODE_UP, Button::Up},
    {SDL_SCANCODE_DOWN, Button::Down},
    {SDL_SCANCODE_LEFT, Button::Left},
    {SDL_SCANCODE_RIGHT, Button::Right},
};

struct GamepadBinding
{
    SDL_GameControllerButton gamepadButton;
    Button button;
};

// The NES has B on the left and A on the right; either the bottom/right pair (like a
// Nintendo controller) or the left/bottom pair of face buttons can be used for B/A.
const GamepadBinding GAMEPAD_BINDINGS[] = {
    {SDL_CONTROLLER_BUTTON_B, Button::A},
    {SDL_CONTROLLER_BUTTON_Y, Button::A},
    {SDL_CONTROLLER_BUTTON_A, Button::B},
    {SDL_CONTROLLER_BUTTON_X, Button::B},
    {SDL_CONTROLLER_BUTTON_BACK, Button::Select},
    {SDL_CONTROLLER_BUTTON_START, Button::Start},
    {SDL_CONTROLLER_BUTTON_DPAD_UP, Button::Up},
    {SDL_CONTROLLER_BUTTON_DPAD_DOWN, Button::Down},
    {SDL_CONTROLLER_BUTTON_DPAD_LEFT, Button::Left},
    {SDL_CONTROLLER_BUTTON_DPAD_RIGHT, Button::Right},
};

/**
 * How far the analog stick has to be pushed to count as a direction.
 */
constexpr int STICK_THRESHOLD = 16000;

using ButtonStates = std::array<bool, 8>;

void readGamepad(SDL_GameController* gamepad, ButtonStates& states)
{
    for (const GamepadBinding& binding : GAMEPAD_BINDINGS)
    {
        states[static_cast<int>(binding.button)] |= SDL_GameControllerGetButton(gamepad, binding.gamepadButton) != 0;
    }

    const int x = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTX);
    const int y = SDL_GameControllerGetAxis(gamepad, SDL_CONTROLLER_AXIS_LEFTY);
    states[static_cast<int>(Button::Left)] |= x < -STICK_THRESHOLD;
    states[static_cast<int>(Button::Right)] |= x > STICK_THRESHOLD;
    states[static_cast<int>(Button::Up)] |= y < -STICK_THRESHOLD;
    states[static_cast<int>(Button::Down)] |= y > STICK_THRESHOLD;
}

} // namespace

void Input::handleEvent(const SDL_Event& event)
{
    if (event.type == SDL_CONTROLLERDEVICEADDED)
    {
        if (SDL_GameController* gamepad = SDL_GameControllerOpen(event.cdevice.which))
        {
            std::cout << "Gamepad connected: " << SDL_GameControllerName(gamepad) << "\n";
            gamepads.emplace_back(gamepad);
        }
    }
    else if (event.type == SDL_CONTROLLERDEVICEREMOVED)
    {
        // For removal events, "which" is the joystick instance ID
        gamepads.erase(std::remove_if(gamepads.begin(), gamepads.end(), [&](const SdlPtr<SDL_GameController>& gamepad) {
            return SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gamepad.get())) == event.cdevice.which;
        }), gamepads.end());
    }
}

void Input::update(SMBEngine& engine) const
{
    for (int player = 0; player < 2; player++)
    {
        ButtonStates states{};

        if (player == 0)
        {
            // Alt+Enter toggles fullscreen rather than pressing Start
            const bool altHeld = (SDL_GetModState() & KMOD_ALT) != 0;
            const Uint8* keys = SDL_GetKeyboardState(nullptr);
            for (const KeyBinding& binding : KEY_BINDINGS)
            {
                if (!(altHeld && binding.key == SDL_SCANCODE_RETURN))
                {
                    states[static_cast<int>(binding.button)] |= keys[binding.key] != 0;
                }
            }
        }

        if (static_cast<std::size_t>(player) < gamepads.size())
        {
            readGamepad(gamepads[player].get(), states);
        }

        for (int button = 0; button < 8; button++)
        {
            engine.getController(player).setButtonState(static_cast<Button>(button), states[button]);
        }
    }
}
