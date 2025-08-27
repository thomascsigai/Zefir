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
		m_DrawCallsCount = 0;

		m_ScreenWidth = 0;
		m_ScreenHeight = 0;
		SDL_GetWindowSize(m_Window->GetSDLWindow(), &m_ScreenWidth, &m_ScreenHeight);

		float offset = 100;
		m_ScreenRect = {
			-offset, -offset,
			(float)m_ScreenWidth + offset, (float)m_ScreenHeight + offset
		};
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
		SDL_SetRenderDrawBlendMode(m_SDLRenderer, SDL_BLENDMODE_BLEND);

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

	void Renderer::RenderFilledRect(const Vector2& position, const Vector2& size, const Camera& cam)
	{
		Vector2 screenPos = Vector2(position);
		screenPos = WorldToScreenPosition(screenPos, m_ScreenWidth, m_ScreenHeight, cam);
		SDL_FRect rect = WorldToScreenRect(screenPos, size, cam);

		if (IsOutsideOfScreen(rect)) return; // Camera Culling

		SDL_RenderFillRectF(m_SDLRenderer, &rect);
		m_DrawCallsCount++;
	}

	void Renderer::RenderRect(const Vector2& position, const Vector2& size, const Camera& cam)
	{
		Vector2 screenPos = Vector2(position);
		screenPos = WorldToScreenPosition(screenPos, m_ScreenWidth, m_ScreenHeight, cam);
		SDL_FRect rect = WorldToScreenRect(screenPos, size, cam);

		if (IsOutsideOfScreen(rect)) return; // Camera Culling

		SDL_RenderDrawRectF(m_SDLRenderer, &rect);
		m_DrawCallsCount++;
	}

	// rotation angle : radians
	void Renderer::RenderStaticTexture(SDL_Texture* texture, const Vector2& position, const Vector2& size,
		const double& rotationAngle, const Camera& cam, bool horizontalFlip, bool verticalFlip)
	{
		Vector2 screenPos = Vector2(position);
		screenPos = WorldToScreenPosition(screenPos, m_ScreenWidth, m_ScreenHeight, cam);
		SDL_FRect rect = WorldToScreenRect(screenPos, size, cam);

		if (IsOutsideOfScreen(rect)) return; // Camera Culling

		double angleDegrees = rotationAngle * 180 / M_PI;

		SDL_RendererFlip flip = horizontalFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		flip = verticalFlip ? (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL) : flip;

		SDL_RenderCopyExF(m_SDLRenderer, texture, NULL, &rect, angleDegrees, NULL, flip);
		m_DrawCallsCount++;
	}

	// rotation angle : radians
	void Renderer::RenderAnimFrame(SDL_Texture* texture, const Vector2& position, const Vector2& size,
		Uint16 frameW, Uint16 frameH, int frameNumber, const double& rotationAngle,
		const Camera& cam, bool horizontalFlip, bool verticalFlip)
	{
		Vector2 screenPos = Vector2(position);
		screenPos = WorldToScreenPosition(screenPos, m_ScreenWidth, m_ScreenHeight, cam);
		SDL_FRect rect = WorldToScreenRect(screenPos, size, cam);
		SDL_Rect frame = { frameNumber * frameW, 0, frameW, frameH };

		if (IsOutsideOfScreen(rect)) return; // Camera Culling

		double angleDegrees = rotationAngle * 180 / M_PI;

		SDL_RendererFlip flip = horizontalFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		flip = verticalFlip ? (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL) : flip;

		SDL_RenderCopyExF(m_SDLRenderer, texture, &frame, &rect, angleDegrees, NULL, flip);
		m_DrawCallsCount++;
	}

	void Renderer::RenderLine(const Vector2& pos1, const Vector2& pos2, const Camera& cam)
	{
		Vector2 screenPos1 = Vector2(pos1);
		screenPos1 = WorldToScreenPosition(screenPos1, m_ScreenWidth, m_ScreenHeight, cam);

		Vector2 screenPos2 = Vector2(pos2);
		screenPos2 = WorldToScreenPosition(screenPos2, m_ScreenWidth, m_ScreenHeight, cam);
				
		SDL_RenderDrawLineF(m_SDLRenderer, screenPos1.x, screenPos1.y, screenPos2.x, screenPos2.y);
		m_DrawCallsCount++;
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

	int Renderer::GetDrawCallsCount()
	{
		return m_DrawCallsCount;
	}

	void Renderer::ResetDrawCallsCounter()
	{
		m_DrawCallsCount = 0;
	}

	bool Renderer::IsOutsideOfScreen(const SDL_FRect& rect)
	{
		//return false;
		// If rect doesn't collide with screen, is outside of screen
		return (rect.x + rect.w < m_ScreenRect.x) ||
			(rect.x > m_ScreenRect.x + m_ScreenRect.w) ||
			(rect.y + rect.h < m_ScreenRect.y) ||
			(rect.y > m_ScreenRect.y + m_ScreenRect.h);
	}

#ifndef NDEBUG
	void Renderer::RenderDebugAxis(const Camera& cam)
	{
		// Draw other lines
		SDL_SetRenderDrawColor(m_SDLRenderer, 80, 80, 80, 100);
		for (int i = 0; i < 2000; i++)
		{
			RenderLine({ -1000, 1000 - (float)i }, { 1000, 1000 - (float)i }, cam);
			RenderLine({ -1000 + (float)i, -1000 }, { -1000 + (float)i, 1000 }, cam);
		}
		
		// Draw x axis
		SDL_SetRenderDrawColor(m_SDLRenderer, 155, 0, 0, 150);
		RenderLine({ -1000, 0 }, { 1000, 0 }, cam);

		// Draw y axis
		SDL_SetRenderDrawColor(m_SDLRenderer, 0, 0, 155, 150);
		RenderLine({ 0, 1000 }, { 0, -1000 }, cam);

		// Reset drawing color to white
		SDL_SetRenderDrawColor(m_SDLRenderer, 255, 255, 255, 100);
	}
#endif
}
