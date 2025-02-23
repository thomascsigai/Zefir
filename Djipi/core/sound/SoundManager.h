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

		bool PlaySound(std::shared_ptr<Sound> sound, bool infiniteLoop = false);

	private:
		bool Init();
		void Shutdown();
	};
}