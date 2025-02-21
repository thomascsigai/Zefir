#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <Renderer.h>
#include <Resource.h>
#include <Log.h>

namespace Djipi
{
	class Texture : public Resource
	{
	public:
		Texture(const std::string& path, Renderer* renderer)
		{
			m_Path = path;
			m_Renderer = renderer;
			m_SDLTexture = nullptr;
		}

		bool Load() override
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
				LOG_WARN("Texture " << m_Path << " could not be loaded." << SDL_GetError());
				return false;
			}

			return true;
		}

		bool Unload() override
		{
			SDL_DestroyTexture(m_SDLTexture);
			return true;
		}

		bool Reload() override
		{
			return Load();
		}

		SDL_Texture* GetSDLTexture() const
		{ 
			return m_SDLTexture; 
		}

	private:
		Renderer* m_Renderer;
		std::string m_Path;
		
		SDL_Texture* m_SDLTexture;
	};
}