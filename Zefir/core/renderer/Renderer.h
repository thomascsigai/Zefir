#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Window.h>

namespace Zefir
{
	class Renderer
	{
	public:
		Renderer(Window* window);
		~Renderer();

		SDL_Renderer* GetSDLRenderer() const { return m_SDLRenderer; }

	private:
		bool Init(Window* window);
		void Shutdown();

		SDL_Renderer* m_SDLRenderer;
	};
}