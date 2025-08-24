#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <core/window/Window.h>
#include <core/math/Vector2.h>
#include <scene/Camera.h>

#include <renderer/UnitConversion.h>

namespace Zefir
{
	class Renderer
	{
	public:
		Renderer(Window* window);
		~Renderer();

		SDL_Renderer* GetSDLRenderer() const { return m_SDLRenderer; }

		void RenderRect(const Vector2& position, const Vector2& size, const Camera& cam);
		void RenderFilledRect(const Vector2& position, const Vector2& size, const Camera& cam);
		
		void RenderCircle(Vector2 position, float radius);
		void RenderFilledCircle(Vector2 position, float radius);
		
		void RenderStaticTexture(SDL_Texture* texture, const Vector2& position, 
			const Vector2& size, const double& rotationAngle, const Camera& cam,
			bool horizontalFlip = false, bool verticalFlip = false);
		
		void RenderAnimFrame(SDL_Texture* texture, const Vector2& position, const Vector2& size,
			Uint16 frameW, Uint16 frameH, int frameNumber, const double& rotationAngle,
			const Camera& cam, bool horizontalFlip = false, bool verticalFlip = false);

		// Given the world coordinates of two points, render a line between them.
		void RenderLine(const Vector2& pos1, const Vector2& pos2, const Camera& cam);

		int GetDrawCallsCount();
		void ResetDrawCallsCounter();

#ifndef NDEBUG

		// Render the world coordinates axis (origin in the center of the screen).
		void RenderDebugAxis(const Camera& cam);

#endif

	private:
		bool IsOutsideOfScreen(SDL_FRect rect);

	private:
		bool Init(Window* window);
		void Shutdown();

		SDL_Renderer* m_SDLRenderer;
		Window* m_Window;

		int m_DrawCallsCount;
	};
}