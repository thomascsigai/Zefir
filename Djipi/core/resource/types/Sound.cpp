#include <Sound.h>

namespace Djipi
{
	Sound::Sound(std::string path) 
		: m_MixChunk(nullptr), m_Path(path) { }

	bool Sound::Load()
	{
		m_MixChunk = Mix_LoadWAV(m_Path.c_str());
		if (m_MixChunk == nullptr)
		{
			LOG_WARN(Mix_GetError());
			return false;
		}

		return true;
	}
	bool Sound::Unload()
	{
		Mix_FreeChunk(m_MixChunk);
		m_MixChunk = nullptr;

		return true;
	}
	bool Sound::Reload()
	{
		return Load();
	}

	Mix_Chunk* Sound::GetMixChunk() const
	{
		return m_MixChunk;
	}
}