#include <Renderer.h>

namespace Djipi
{
	Renderer::Renderer(Window* window)
	{
		if (!Init(window))
		{
			LOG_FATAL("Unable to init Renderer System.");
		}
	}

	Renderer::~Renderer()
	{
		Shutdown();
	}

	bool Renderer::Init(Window* window)
	{
		bool success = true;

		if (window->GetSDLWindow() == nullptr)
		{
			LOG_FATAL("Window cannot be null while creating renderer !");
			success = false;
		}

		m_SDLRenderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);

		if (m_SDLRenderer == nullptr)
		{
			LOG_FATAL("Renderer could not be created ! SDL_Error: " << SDL_GetError());
			success = false;
		}

		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			LOG_WARN("SDL_image could not initialize! SDL_image Error: " << IMG_GetError());
			success = false;
		}

		if (TTF_Init() < 0)
		{
			LOG_WARN("SDL_ttf could not initialize : " << TTF_GetError());
			success = false;
		}

		return success;
	}

	void Renderer::Shutdown()
	{
		TTF_Quit();
		IMG_Quit();

		SDL_DestroyRenderer(m_SDLRenderer);
		m_SDLRenderer = nullptr;
	}
}
