#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>
#include <scene/UI/UIText.h>

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

			AddUIToScene(std::make_unique<Zefir::UIText>(
				0.0f, 2.0f, // Position
				10.0f, 0.6f, // Size
				std::string("Click anywhere to spawn square"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				10, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
			
			AddUIToScene(std::make_unique<Zefir::UIText>(
				0.0f, 1.0f, // Position
				11.0f, 0.6f, // Size
				std::string("Press T to update text, R to remove it"), // Text
				m_EngineContext->resourceManager->GetFont("resources\\fonts\\bit5x3.ttf"), // Font
				10, SDL_Color(255, 255, 255, 255) // Font Size, Color
			));
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene unloaded");
		}

		void OnUpdate() override
		{
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

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_t)
				{
					APP_LOG_INFO("Text updated");
					static_cast<Zefir::UIText*>(m_UIObjects[0].get())->SetText("Text Update");
					m_UIObjects[0]->m_Size = { 7.0f, 1.2f };
				}

				if (e.key.keysym.sym == SDLK_r)
				{
					APP_LOG_INFO("Text removed");
					RemoveUI(0);
				}
			}
		}
	};
}