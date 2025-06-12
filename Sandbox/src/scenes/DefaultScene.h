#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>
#include <gameobjects/Player.h>

namespace ZefirApp
{
	SDL_Texture* text;

	class DefaultScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			APP_LOG_INFO("Scene load");
			m_Cam.zoom = -20;
			AddObjectToScene(std::make_unique<ZefirApp::Player>(ZefirApp::Player(
				m_EngineContext->resourceManager->GetTexture("resources\\textures\\player.png"),
				m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\cat.png")
			)));
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene unload");
		}

		void OnUpdate() override
		{
			m_Cam.position = m_SceneObjects[0]->m_Transform2D.position;
		}

		void OnSceneEvent(const SDL_Event& e)
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				if (e.key.keysym.sym == SDLK_e)
				{
					APP_LOG_INFO("Test");
					m_EngineContext->soundManager->PlaySound(
						m_EngineContext->resourceManager->GetSound("resources\\sounds\\win1.wav")
					);
				}
			}
		}
	};
}