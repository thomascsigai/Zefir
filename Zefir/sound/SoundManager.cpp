#include <sound/SoundManager.h>

namespace Zefir
{
	SoundManager::SoundManager()
	{
		Init();
	}
	SoundManager::~SoundManager()
	{
		Shutdown();
	}

	bool SoundManager::PlaySound(std::shared_ptr<Sound> sound, int loops)
	{
		if (sound == nullptr)
		{
			LOG_WARN("Sound does not exist and could not be played.");
			return false;
		}

		Mix_Chunk* chunk = sound->GetMixChunk();
		if (chunk == nullptr)
		{
			LOG_WARN("Mix_Chunk is null, sound could not be played.");
			return false;
		}

		Mix_PlayChannel(-1, sound->GetMixChunk(), loops);
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