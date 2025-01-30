#include <Texture.h>

namespace Djipi
{
	Texture::Texture()
	{
		m_Texture = NULL;
		m_Width = 0;
		m_Height = 0;
	}

	Texture::~Texture()
	{
		Free();
	}

	bool Texture::LoadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer)
	{
		Free();

		SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
		if (textSurface == NULL)
		{
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			m_Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (m_Texture == NULL)
			{
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				m_Width = textSurface->w;
				m_Height = textSurface->h;
			}

			SDL_FreeSurface(textSurface);
		}

		return m_Texture != NULL;
	}

	void Texture::Free()
	{
		if (m_Texture != NULL)
		{
			SDL_DestroyTexture(m_Texture);
			m_Texture = NULL;
			m_Width = 0;
			m_Height = 0;
		}
	}

	void Texture::Render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		SDL_Rect renderQuad = { x, y, m_Width, m_Height };

		if (clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		SDL_RenderCopyEx(renderer, m_Texture, clip, &renderQuad, angle, center, flip);
	}

	void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
	{
		SDL_SetTextureColorMod(m_Texture, red, green, blue);
	}

	void Texture::SetBlendMode(SDL_BlendMode blending)
	{
		SDL_SetTextureBlendMode(m_Texture, blending);
	}

	void Texture::SetAlpha(Uint8 alpha)
	{
		SDL_SetTextureAlphaMod(m_Texture, alpha);
	}
}
