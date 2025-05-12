#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Window.h>
#include <Vector2.h>

namespace Zefir
{
	class Renderer
	{
	public:
		Renderer(Window* window);
		~Renderer();

		SDL_Renderer* GetSDLRenderer() const { return m_SDLRenderer; }

		void RenderFilledRect(Vector2 position, Vector2 size);
		void RenderCircle(Vector2 position, float radius);
		void RenderFilledCircle(Vector2 position, float radius);
		void RenderStaticTexture(SDL_Texture* texture, Vector2 position, Vector2 size,
			double rotationAngle);
		void RenderAnimFrame(SDL_Texture* texture, Vector2 position, Vector2 size,
			Uint16 frameW, Uint16 frameH, int frameNumber, double rotationAngle);

	private:
		bool Init(Window* window);
		void Shutdown();

		SDL_Renderer* m_SDLRenderer;
	};
}