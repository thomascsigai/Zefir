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
		SDL_Window* GetWindow() const { return m_Window; }


	private:
		bool Init() override;
		void Shutdown() override;

		SDL_Window* m_Window;
	};
}