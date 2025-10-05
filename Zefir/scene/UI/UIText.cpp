#include <scene/UI/UIText.h>
#include <renderer/UnitConversion.h>

namespace Zefir
{
	UIText::UIText(float x, float y, const std::string& text, std::shared_ptr<Font> font,
		int fontSize, SDL_Color color)
		: UIObject(x, y, 0, 0), m_Text(text), m_Font(font), m_FontSize(fontSize), m_Color(color)
	{
		m_SDLTexture = nullptr;
		LoadTextSurface();
	}

	UIText::~UIText()
	{
		if (m_SDLTexture)
		{
			SDL_DestroyTexture(m_SDLTexture);
		}
		if (m_SDLSurface)
		{
			SDL_FreeSurface(m_SDLSurface);
		}
	}

	void UIText::Update()
	{
		 
	}

	void UIText::Render(Renderer* renderer, const Camera& cam)
	{
		if (m_SDLTexture == nullptr)
		{
			CreateTextTexture(renderer);
		}

		renderer->RenderStaticTexture(m_SDLTexture, m_Position, m_SDLTextureSize, 0,
			cam, false, false);
	}

	void UIText::LoadTextSurface()
	{
		if (m_SDLTexture != nullptr)
		{
			SDL_DestroyTexture(m_SDLTexture);
			m_SDLTexture = nullptr;
		}

		if (m_Font == nullptr)
		{
			LOG_WARN("Font not found while loading UI Text object.");
		}

		TTF_Font* fontTTF = m_Font->GetFontTTF();
		TTF_SetFontSize(fontTTF, m_FontSize);

		m_SDLSurface = TTF_RenderText_Solid(fontTTF, m_Text.c_str(), m_Color);
		if (m_SDLSurface == nullptr)
		{
			LOG_WARN("Unable to load text surface! SDL_ttf Error: ", TTF_GetError());
		}
	}

	void UIText::CreateTextTexture(Renderer* renderer)
	{
		m_SDLTexture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(), m_SDLSurface);
		if (m_SDLTexture == nullptr)
		{
			LOG_WARN("Unable to create texture from rendered text! SDL Error: ", SDL_GetError());
		}
		SDL_FreeSurface(m_SDLSurface);

		int width, height;
		SDL_QueryTexture(m_SDLTexture, NULL, NULL, &width, &height);

		m_SDLTextureSize = { (float)width / PIXELS_PER_METER, (float)height / PIXELS_PER_METER };
	}

	void UIText::SetText(const std::string& text)
	{
		if (m_Text != text)
		{
			m_Text = text;
			LoadTextSurface();
			m_SDLTexture = nullptr;
		}
	}

	void UIText::SetFontSize(int size)
	{
		if (m_FontSize != size)
		{
			m_FontSize = size;
			LoadTextSurface();
			m_SDLTexture = nullptr;
		}
	}

	void UIText::SetFont(std::shared_ptr<Font> font)
	{
		if (m_Font != font)
		{
			m_Font = font;
			LoadTextSurface();
			m_SDLTexture = nullptr;
		}
	}
}