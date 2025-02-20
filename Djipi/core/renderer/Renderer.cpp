#include <Renderer.h>

namespace Djipi
{
	Renderer::Renderer(Window* window) : m_Window(window)
	{
		if (!Init())
		{
			LOG_FATAL("Unable to init Renderer System.");
		}
	}

	Renderer::~Renderer()
	{
		Shutdown();
	}

	bool Renderer::Init()
	{
		bool success = true;

		if (m_Window->GetSDLWindow() == nullptr)
		{
			LOG_FATAL("Window cannot be null while creating renderer !");
			success = false;
		}

		m_SDLRenderer = SDL_CreateRenderer(m_Window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);

		if (m_SDLRenderer == nullptr)
		{
			LOG_FATAL("Renderer could not be created ! SDL_Error: " << SDL_GetError());
			success = false;
		}

		m_Window = nullptr;
		return success;
	}

	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(m_SDLRenderer);
		m_SDLRenderer = nullptr;
	}
}


//if (TTF_Init() < 0)
//{
//	std::cerr << "SDL_ttf could not initialize : " << TTF_GetError() << std::endl;
//	success = false;
//}
//
////Initialize SDL_mixer
//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
//{
//	std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
//	success = false;
//}