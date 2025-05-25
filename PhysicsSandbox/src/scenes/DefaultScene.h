#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>

#include <gameobjects/PhysicObject.h>
#include <gameobjects/Ground.h>

namespace ZefirApp
{
	class DefaultScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			APP_LOG_INFO("Scene loaded");

			AddObjectToScene(std::make_unique<Ground>(100, 500));
			
			for (int i = 0; i < 100; i++)
			{
				AddObjectToScene(std::make_unique<PhysicObject>(5 * i + 20, i));
			}
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene unloaded");
		}

		void OnSceneEvent(const SDL_Event& e)
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