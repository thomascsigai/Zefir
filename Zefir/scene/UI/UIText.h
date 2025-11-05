#pragma once

#include <scene/UI/UIObject.h>
#include <resource/types/Font.h>

namespace Zefir
{
	class UIText : public UIObject
	{
	public:
		UIText(float x, float y, const std::string& text, std::shared_ptr<Font> font,
			int fontSize, SDL_Color color);
		~UIText();

		void Update() override;
		void Render(Renderer* renderer, const Camera& cam) override;

		void SetText(const std::string& text);
		void SetFontSize(int size);
		void SetFont(std::shared_ptr<Font> font);

	private:
		std::string m_Text;
		int m_FontSize;
		std::shared_ptr<Font> m_Font;
		SDL_Color m_Color;

		void LoadTextSurface();
		void CreateTextTexture(Renderer* renderer);

		SDL_Texture* m_SDLTexture;
		Vector2 m_SDLTextureSize;
		SDL_Surface* m_SDLSurface;
	};
}