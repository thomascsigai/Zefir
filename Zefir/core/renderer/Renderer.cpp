#include <Renderer.h>

namespace Zefir
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

	void Renderer::RenderFilledRect(Vector2 position, Vector2 size)
	{
		SDL_FRect rect = {
			position.x, position.y,
			size.x, size.y
		};
		SDL_RenderFillRectF(m_SDLRenderer, &rect);
	}

	void Renderer::RenderStaticTexture(SDL_Texture* texture, Vector2 position, Vector2 size)
	{
		SDL_Rect rect = {
				position.x, position.y,
				size.x, size.y
		};
		SDL_RenderCopy(m_SDLRenderer, texture, NULL, &rect);
	}

	void Renderer::RenderAnimFrame(SDL_Texture* texture, Vector2 position, Vector2 size,
		Uint16 frameW, Uint16 frameH, int frameNumber)
	{
		SDL_Rect rect = {
				position.x, position.y,
				size.x, size.y
		};
		SDL_Rect frame = {
			frameNumber * frameW, 0, frameW, frameH
		};
		SDL_RenderCopy(m_SDLRenderer, texture, &frame, &rect);
	}
}
