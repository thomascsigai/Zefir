#pragma once

#include <SDL.h>
#include <iostream>

#include <GameConfig.h>
#include <Log.h>

namespace Djipi
{
	class Window
	{
	public:
		Window();
		~Window();
		SDL_Window* GetSDLWindow() const { return m_SDLWindow; }

	private:
		bool Init();
		void Shutdown();

		SDL_Window* m_SDLWindow;
	};
}