#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <resource/ResourceManager.h>
#include <renderer/Renderer.h>

namespace Zefir
{
	void LoadText(SDL_Texture*& textPtr, std::string textToLoad, int fontSize, ResourceManager* resourceManager, Renderer* renderer, SDL_Color color);
	void RenderText(SDL_Texture* textTexture, Renderer* renderer, int x, int y);
}

