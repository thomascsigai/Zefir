#pragma once

#include <iostream>
#include <SDL_mixer.h>

#include <IResource.h>
#include <Log.h>

namespace Zefir
{
	class Sound : public IResource
	{
	public:
		Sound(std::string path);

		bool Load();
		bool Unload();
		bool Reload();

		Mix_Chunk* GetMixChunk() const;

	private:
		Mix_Chunk* m_MixChunk;
		std::string m_Path;
	};
}