#pragma once

#include <string>
#include <SDL_ttf.h>

#include <Resource.h>
#include <Log.h>

namespace Djipi
{
	class Font : public Resource
	{
	public:
		Font(std::string path);

		bool Load() override;
		bool Unload() override;
		bool Reload() override;

		TTF_Font* GetFontTTF() const;

	private:
		std::string m_Path;
		TTF_Font* m_FontTTF;
	};
}