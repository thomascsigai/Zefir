#pragma once

#include <SDL_mixer.h>

namespace Djipi
{
	class Sound : public Resource
	{
	private:
		Mix_Chunk* m_Sound;
	};
}