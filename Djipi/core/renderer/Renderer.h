#pragma once

#include <SDL.h>
#include <DjipiSystem.h>
#include <Window.h>

namespace Djipi
{
	class Renderer : public DjipiSystem
	{
	public:
		Renderer(Window* window);
		~Renderer() override;

		SDL_Renderer* GetSDLRenderer() const { return m_SDLRenderer; }

	private:
		bool Init() override;
		void Shutdown() override;

		Window* m_Window;

		SDL_Renderer* m_SDLRenderer;
	};
}