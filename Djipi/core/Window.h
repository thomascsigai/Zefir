#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>
#include <GameConfig.h>

namespace Djipi
{
	class Window
	{
	public:
		Window();

		bool Init();

		void Close();

		SDL_Window* GetWindow() { return m_Window; }
		SDL_Renderer* GetRenderer() { return m_Renderer; }

	private:
		SDL_Renderer* m_Renderer;
		SDL_Window* m_Window;
	};
}