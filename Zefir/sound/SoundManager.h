#pragma once

#include <SDL_mixer.h>
#include <resource/types/Sound.h>

namespace Zefir
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