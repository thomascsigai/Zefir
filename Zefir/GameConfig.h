#pragma once

#include <SDL.h>
#include <core/math/Vector2.h>

// WINDOW SETTINGS --------------------------------------------------

constexpr Uint16 SCREEN_WIDTH = 800;
constexpr Uint16 SCREEN_HEIGHT = 600;


// RESOURCES SETTINGS ---------------------------------------------------

#define RESOURCES_BASE_DIR "resources"
#define RESOURCES_TEXTURES_DIR "textures"
#define RESOURCES_ANIM_DIR "anims"
#define RESOURCES_SOUNDS_DIR "sounds"
#define RESOURCES_FONTS_DIR "fonts"


// GAME SPECIFIC SETTINGS -------------------------------------------

constexpr Uint16 PLAYER_SPEED = 100;

// PHYSICS SETTINGS -------------------------------------------------

const Zefir::Vector2 GRAVITY_FORCE(0, 200.0f);

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
