#include <resource/types/Texture.h>

namespace Zefir
{
	Texture::Texture(const std::string& path, Renderer* renderer)
		: m_Path(path), m_Renderer(renderer)
	{
		m_SDLTexture = nullptr;
	}

	bool Texture::Load()
	{
		if (m_SDLTexture != nullptr)
		{
			Unload();
		}

		if (m_Renderer == nullptr)
		{
			LOG_WARN("Renderer could not be null while loading texture.");
			return false;
		}

		SDL_Surface* surface = IMG_Load(m_Path.c_str());
		if (surface == nullptr)
		{
			LOG_WARN("Surface for texture " << m_Path << " not created." << SDL_GetError());
			return false;
		}

		m_SDLTexture = SDL_CreateTextureFromSurface(m_Renderer->GetSDLRenderer(), surface);
		SDL_FreeSurface(surface);

		if (m_SDLTexture == nullptr)
		{
			LOG_WARN(SDL_GetError());
			return false;
		}

		return true;
	}

	bool Texture::Unload()
	{
		SDL_DestroyTexture(m_SDLTexture);
		return true;
	}

	bool Texture::Reload()
	{
		return Load();
	}

	SDL_Texture* Texture::GetSDLTexture() const
	{
		return m_SDLTexture;
	}

	bool Texture::IsAnimated()
	{
		return false;
	}
}