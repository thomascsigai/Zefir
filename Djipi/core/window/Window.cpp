#include <Window.h>

namespace Djipi
{
	Window::Window()
	{
		Init();
	}

	Window::~Window()
	{
		Shutdown();
	}

	bool Window::Init()
	{
		bool success = true;

		m_Window = SDL_CreateWindow("Djipi App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (m_Window == NULL)
		{
			LOG_FATAL("Window could not be created ! SDL_Error: " << SDL_GetError());
			success = false;
		}

		return success;
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}
}