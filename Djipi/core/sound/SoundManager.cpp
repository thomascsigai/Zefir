#include <SoundManager.h>

namespace Djipi
{
	SoundManager::SoundManager()
	{
		Init();
	}
	SoundManager::~SoundManager()
	{
		Shutdown();
	}

	bool SoundManager::PlaySound(std::shared_ptr<Sound> sound, bool infiniteLoop)
	{
		if (sound == nullptr)
		{
			LOG_WARN("Sound does not exist and could not be played.");
			return false;
		}

		int loop;
		infiniteLoop ? loop = -1 : loop = 0;

		Mix_Chunk* chunk = sound->GetMixChunk();
		if (chunk == nullptr)
		{
			LOG_WARN("Mix_Chunk is null, sound could not be played.");
			return false;
		}

		Mix_PlayChannel(-1, sound->GetMixChunk(), loop);
		return true;
	}

	bool SoundManager::Init()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			LOG_WARN("SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError());
			return false;
		}

		return true;
	}

	void SoundManager::Shutdown()
	{
		Mix_Quit();
	}
}