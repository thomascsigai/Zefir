#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include <Resource.h>

namespace Djipi
{
	class Texture : public Resource
	{
	public:

	private:
		SDL_Texture* m_Texture;
	};
}