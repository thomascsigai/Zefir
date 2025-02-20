#pragma once

#include <SDL.h>
#include <iostream>

#include <GameConfig.h>
#include <Log.h>
#include <DjipiSystem.h>

namespace Djipi
{
	class Window : public DjipiSystem
	{
	public:
		Window();
		~Window() override;
		SDL_Window* GetSDLWindow() const { return m_SDLWindow; }

	private:
		bool Init() override;
		void Shutdown() override;

		SDL_Window* m_SDLWindow;
	};
}