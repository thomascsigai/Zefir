#pragma once

#include <string>
#include <SDL_ttf.h>

#include <resource/IResource.h>
#include <core/debug/Log.h>

namespace Zefir
{
	class Font : public IResource
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