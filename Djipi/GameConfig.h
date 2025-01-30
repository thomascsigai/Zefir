#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

// WINDOW SETTINGS --------------------------------------------------

constexpr Uint16 SCREEN_WIDTH = 800;
constexpr Uint16 SCREEN_HEIGHT = 600;


// RESOURCES SETTINGS ---------------------------------------------------

#define RESOURCES_DIR_PATH "resources/"


// GAME SPECIFIC SETTINGS -------------------------------------------

constexpr Uint16 PLAYER_SPEED = 100;

// KEYBINDS ---------------------------------------------------------

// Paddles keybinds
struct MoveKeybind
{
	SDL_Keycode UP;
	SDL_Keycode DOWN;
	SDL_Keycode LEFT;
	SDL_Keycode RIGHT;
};

constexpr MoveKeybind MOVE_KEYBIND = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };
