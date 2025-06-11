#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <core/window/Window.h>
#include <core/math/Vector2.h>

#include <renderer/UnitConversion.h>

namespace Zefir
{
	class Renderer
	{
	public:
		Renderer(Window* window);
		~Renderer();

		SDL_Renderer* GetSDLRenderer() const { return m_SDLRenderer; }

		void RenderRect(Vector2 position, Vector2 size);
		void RenderFilledRect(Vector2 position, Vector2 size);
		void RenderCircle(Vector2 position, float radius);
		void RenderFilledCircle(Vector2 position, float radius);
		void RenderStaticTexture(SDL_Texture* texture, Vector2 position, Vector2 size,
			double rotationAngle);
		void RenderAnimFrame(SDL_Texture* texture, Vector2 position, Vector2 size,
			Uint16 frameW, Uint16 frameH, int frameNumber, double rotationAngle);

		// Given the world coordinates of two points, render a line between them.
		void RenderLine(Vector2 pos1, Vector2 pos2);

#ifndef NDEBUG

		// Render the world coordinates axis (origin in the center of the screen).
		void RenderDebugAxis();

#endif

	private:
		bool Init(Window* window);
		void Shutdown();

		SDL_Renderer* m_SDLRenderer;
		Window* m_Window;
	};
}