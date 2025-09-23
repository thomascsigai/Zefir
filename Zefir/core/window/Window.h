#pragma once

#include <SDL.h>
#include <iostream>

#include <core/window/WindowSettings.h>
#include <core/debug/Log.h>

namespace Zefir
{
	class Window
	{
	public:
		Window();
		~Window();

		void SetSettings(const WindowSettings&);

		SDL_Window* GetSDLWindow() const { return m_SDLWindow; }
		WindowSettings GetWindowSettings() const { return m_Settings; }

	private:
		bool Init();
		void Shutdown();

		SDL_Window* m_SDLWindow;
		WindowSettings m_Settings;
	};
}