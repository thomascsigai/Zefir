#include <Window.h>

namespace Djipi
{
	Window::Window()
	{
		if (!Init())
		{
			LOG_FATAL("Unable to init Window System.");
		}
	}

	Window::~Window()
	{
		Shutdown();
	}

	bool Window::Init()
	{
		bool success = true;

		m_SDLWindow = SDL_CreateWindow("Djipi App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_SDLWindow == nullptr)
		{
			LOG_FATAL("SDL Window could not be created ! SDL_Error: " << SDL_GetError());
			success = false;
		}

		return success;
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(m_SDLWindow);
		m_SDLWindow = nullptr;
	}
}