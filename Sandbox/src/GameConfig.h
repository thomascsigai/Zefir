#pragma once

#include <core/window/WindowSettings.h>

namespace ZefirApp
{
	// Paddles keybinds
	struct MoveKeybind
	{
		SDL_Keycode UP;
		SDL_Keycode DOWN;
		SDL_Keycode LEFT;
		SDL_Keycode RIGHT;
	};

	constexpr MoveKeybind MOVE_KEYBIND = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };
}