#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>

#include <gameobjects/PhysicObject.h>
#include <gameobjects/Ground.h>

namespace ZefirApp
{
	SDL_Texture* text;
	SDL_Texture* text2;

	class DefaultScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			AddObjectToScene(std::make_unique<Ground>(100, 500));
			
			for (int i = 0; i < 5; i++)
			{
				AddObjectToScene(std::make_unique<PhysicObject>(150 * i + 20, 20 * i));
			}
		}

		void OnUnload() override
		{
		}

		void OnEvent(const SDL_Event& e)
		{
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					int mouseX = e.button.x;
					int mouseY = e.button.y;

					AddObjectToScene(std::make_unique<PhysicObject>(mouseX, mouseY));
				}
			}
		}
	};
}