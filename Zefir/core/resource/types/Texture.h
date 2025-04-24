#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <Renderer.h>
#include <Resource.h>
#include <Log.h>

namespace Zefir
{
	class Texture : public Resource
	{
	public:
		Texture(const std::string& path, Renderer* renderer);

		bool Load() override;
		bool Unload() override;
		bool Reload() override;

		SDL_Texture* GetSDLTexture() const;

	private:
		Renderer* m_Renderer;
		std::string m_Path;
		
		SDL_Texture* m_SDLTexture;
	};
}