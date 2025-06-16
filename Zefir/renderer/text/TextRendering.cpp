#include <renderer/text/TextRendering.h>

namespace Zefir
{
	void LoadText(SDL_Texture*& textPtr, std::string textToLoad, int fontSize, ResourceManager* resourceManager, Renderer* renderer, SDL_Color color)
	{
		if (textPtr != nullptr)
		{
			SDL_DestroyTexture(textPtr);
			textPtr = nullptr;
		}

		std::shared_ptr<Zefir::Font> font = resourceManager->GetFont("resources\\fonts\\bit5x3.ttf");
		if (font == nullptr)
		{
			LOG_WARN("Font not found.");
			return;
		}

		TTF_Font* fontTTF = font->GetFontTTF();
		TTF_SetFontSize(fontTTF, fontSize);

		SDL_Surface* textSurface = TTF_RenderText_Solid(fontTTF, textToLoad.c_str(), color);
		if (textSurface == nullptr)
		{
			LOG_WARN("Unable to render text surface! SDL_ttf Error: ", TTF_GetError());
		}
		else
		{
			textPtr = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(), textSurface);
			if (textPtr == nullptr)
			{
				LOG_WARN("Unable to create texture from rendered text! SDL Error: ", SDL_GetError());
			}

			SDL_FreeSurface(textSurface);
		}
	}

	void RenderText(SDL_Texture* textTexture, Zefir::Renderer* renderer, int x, int y)
	{
		int texWidth, texHeight;
		SDL_QueryTexture(textTexture, NULL, NULL, &texWidth, &texHeight);

		SDL_Rect rect = { x, y, texWidth, texHeight };
		SDL_RenderCopy(renderer->GetSDLRenderer(), textTexture, NULL, &rect);
	}
}
