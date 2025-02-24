#pragma once

#include <SDL_mixer.h>
#include <Sound.h>

namespace Djipi
{
	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();

		bool PlaySound(std::shared_ptr<Sound> sound, int loops = 0);

	private:
		bool Init();
		void Shutdown();
	};
}