#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>

#include <gameobjects/PhysicObject.h>
#include <gameobjects/Ground.h>

#include <renderer/UnitConversion.h>

namespace ZefirApp
{
	class DefaultScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			APP_LOG_INFO("Scene loaded");

			std::unique_ptr<Zefir::GameObject> ground = std::make_unique<Ground>(0.0f, -5.0f);
			//ground->SetTexture(m_EngineContext->resourceManager->GetTexture("resources\\textures\\bloc.png"));
			AddObjectToScene(std::move(ground));
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
					int screenWidth, screenHeight;
					SDL_GetWindowSize(m_EngineContext->window->GetSDLWindow(), &screenWidth, &screenHeight);
					
					Zefir::Vector2 worldCoords = Zefir::ScreenToWorld({ (float)mouseX, (float)mouseY }, m_EngineContext->window, m_Cam);

					AddObjectToScene(std::make_unique<PhysicObject>(worldCoords.x, worldCoords.y, 
						m_EngineContext->resourceManager->GetTexture("resources\\textures\\bloc.jpg")));
				}
			}
		}
	};
}