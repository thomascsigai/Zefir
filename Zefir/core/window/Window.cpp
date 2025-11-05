#include <core/window/Window.h>
#include <core/EngineEvents.h>

namespace Zefir
{
	Window::Window() : m_Settings()
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

		m_SDLWindow = SDL_CreateWindow(m_Settings.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Settings.width, m_Settings.height, SDL_WINDOW_SHOWN);

		if (m_SDLWindow == nullptr)
		{
			LOG_FATAL("SDL Window could not be created ! SDL_Error: ", SDL_GetError());
			success = false;
		}

		return success;
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(m_SDLWindow);
		m_SDLWindow = nullptr;
	}

	void Window::SetSettings(const WindowSettings& settings)
	{
		SDL_SetWindowTitle(m_SDLWindow, settings.title.c_str());
		SDL_SetWindowSize(m_SDLWindow, settings.width, settings.height);
		SDL_RenderSetVSync(SDL_GetRenderer(m_SDLWindow), settings.vsync);

		m_Settings = settings;

		SDL_Event e;
		e.type = EngineEvents::WINDOW_RESIZE;
		SDL_PushEvent(&e);
	}
}