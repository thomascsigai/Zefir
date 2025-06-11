#include <renderer/Renderer.h>

namespace Zefir
{
	Renderer::Renderer(Window* window)
	{
		if (!Init(window))
		{
			LOG_FATAL("Unable to init Renderer System.");
		}

		m_Window = window;
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

		m_SDLRenderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (m_SDLRenderer == nullptr)
		{
			LOG_FATAL("Renderer could not be created ! SDL_Error: ", SDL_GetError());
			success = false;
		}

		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			LOG_WARN("SDL_image could not initialize! SDL_image Error: ", IMG_GetError());
			success = false;
		}

		if (TTF_Init() < 0)
		{
			LOG_WARN("SDL_ttf could not initialize : ", TTF_GetError());
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
		Vector2 screenPos = WorldToScreenPosition(position, m_Window);
		SDL_Rect rect = WorldToScreenRect(screenPos, size);

		SDL_RenderFillRect(m_SDLRenderer, &rect);
	}

	void Renderer::RenderRect(Vector2 position, Vector2 size)
	{
		Vector2 screenPos = WorldToScreenPosition(position, m_Window);
		SDL_Rect rect = WorldToScreenRect(screenPos, size);

		SDL_RenderDrawRect(m_SDLRenderer, &rect);
	}

	// rotation angle : radians
	void Renderer::RenderStaticTexture(SDL_Texture* texture, Vector2 position, Vector2 size, 
		double rotationAngle)
	{
		Vector2 screenPos = WorldToScreenPosition(position, m_Window);
		SDL_Rect rect = WorldToScreenRect(screenPos, size);

		double angleDegrees = rotationAngle * 180 / M_PI;

		SDL_RenderCopyEx(m_SDLRenderer, texture, NULL, &rect, angleDegrees, NULL, SDL_FLIP_NONE);
	}

	// rotation angle : radians
	void Renderer::RenderAnimFrame(SDL_Texture* texture, Vector2 position, Vector2 size,
		Uint16 frameW, Uint16 frameH, int frameNumber, double rotationAngle)
	{
		Vector2 screenPos = WorldToScreenPosition(position, m_Window);
		SDL_Rect rect = WorldToScreenRect(screenPos, size);
		SDL_Rect frame = { frameNumber * frameW, 0, frameW, frameH };

		double angleDegrees = rotationAngle * 180 / M_PI;

		SDL_RenderCopyEx(m_SDLRenderer, texture, &frame, &rect, angleDegrees, NULL, SDL_FLIP_NONE);
	}

	void Renderer::RenderCircle(Vector2 position, float radius)
	{
		// TO DO

		/*const int centerX = static_cast<int>(position.x);
		const int centerY = static_cast<int>(position.y);
		const int r = static_cast<int>(radius);

		for (int w = 0; w < 360; w++)
		{
			float angle = w * M_PI / 180.0f;
			int x = static_cast<int>(centerX + r * cosf(angle));
			int y = static_cast<int>(centerY + r * sinf(angle));
			SDL_RenderDrawPoint(m_SDLRenderer, x, y);
		}*/
	}

	void Renderer::RenderFilledCircle(Vector2 position, float radius)
	{
		// TO DO

		/*const int centerX = static_cast<int>(position.x);
		const int centerY = static_cast<int>(position.y);
		const int r = static_cast<int>(radius);

		for (int y = -r; y <= r; y++)
		{
			int dx = static_cast<int>(sqrtf(r * r - y * y));
			int x1 = centerX - dx;
			int x2 = centerX + dx;
			SDL_RenderDrawLine(m_SDLRenderer, x1, centerY + y, x2, centerY + y);
		}*/
	}

	void Renderer::RenderLine(Vector2 pos1, Vector2 pos2)
	{
		Vector2 screenPos1 = WorldToScreenPosition(pos1, m_Window);
		Vector2 screenPos2 = WorldToScreenPosition(pos2, m_Window);
				
		SDL_RenderDrawLineF(m_SDLRenderer, screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y);
	}

#ifndef NDEBUG
	void Renderer::RenderDebugAxis()
	{
		// Draw other lines
		SDL_SetRenderDrawColor(m_SDLRenderer, 64, 64, 64, 100);
		for (int i = 0; i < 2000; i++)
		{
			RenderLine({ -1000, 1000 - (float)i }, { 1000, 1000 - (float)i });
			RenderLine({ -1000 + (float)i, -1000 }, { -1000 + (float)i, 1000 });
		}
		
		// Draw x & y axis
		SDL_SetRenderDrawColor(m_SDLRenderer, 155, 0, 0, 100);
		RenderLine({ -1000, 0 }, { 1000, 0 });
		SDL_SetRenderDrawColor(m_SDLRenderer, 0, 0, 155, 100);
		RenderLine({ 0, 1000 }, { 0, -1000 });

		// Reset drawing color to white
		SDL_SetRenderDrawColor(m_SDLRenderer, 255, 255, 255, 100);
	}
#endif
}
