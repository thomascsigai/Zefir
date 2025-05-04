#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include <Renderer.h>
#include <IResource.h>
#include <Log.h>

namespace Zefir
{
	class Texture : public IResource
	{
	public:
		Texture(const std::string& path, Renderer* renderer);

		bool Load() override;
		bool Unload() override;
		bool Reload() override;

		SDL_Texture* GetSDLTexture() const;

		virtual bool IsAnimated(); // Return false by default

	protected:
		Renderer* m_Renderer;
		std::string m_Path;
		
		SDL_Texture* m_SDLTexture;
	};
}