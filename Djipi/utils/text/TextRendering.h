#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <ResourceManager.h>
#include <Renderer.h>

namespace Djipi
{
	void LoadText(SDL_Texture*& textPtr, std::string textToLoad, int fontSize, ResourceManager& resources, Renderer& renderer, SDL_Color color);
	void RenderText(SDL_Texture* textTexture, Renderer& renderer, int x, int y);
}

