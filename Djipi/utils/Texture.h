#pragma once

#include <iostream>d
#include <SDL.h>
#include <SDL_ttf.h>

namespace Djipi
{
	class Texture
	{
	public:
		Texture();
		~Texture();

		bool LoadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);

		void Free();

		void SetColor(Uint8 red, Uint8 green, Uint8 blue);

		void SetBlendMode(SDL_BlendMode blending);

		void SetAlpha(Uint8 alpha);

		void Render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,
			SDL_RendererFlip flip = SDL_FLIP_NONE);

		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; };

	private:
		SDL_Texture* m_Texture;

		int m_Width;
		int m_Height;
	};
}