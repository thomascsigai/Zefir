#include <resource/types/Font.h>

namespace Zefir
{
	Font::Font(std::string path) 
		: m_Path(path), m_FontTTF(nullptr) { }

	bool Font::Load()
	{
		if (m_FontTTF != nullptr)
		{
			Unload();
		}

		m_FontTTF = TTF_OpenFont(m_Path.c_str(), 1);

		if (m_FontTTF == nullptr)
		{
			LOG_WARN(TTF_GetError());
			return false;
		}

		return true;
	}

	bool Font::Unload()
	{
		TTF_CloseFont(m_FontTTF);
		return true;
	}

	bool Font::Reload()
	{
		return Load();
	}

	TTF_Font* Font::GetFontTTF() const
	{
		return m_FontTTF;
	}
}