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
			Zefir::LoadText(text, "Scene 1", 50, m_EngineContext->resourceManager, m_EngineContext->renderer, { 255, 255, 255, 255 });
			player = std::make_unique<ZefirApp::Player>(ZefirApp::Player(m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\cat.png"), nullptr));
			player2 = std::make_unique<ZefirApp::Player>(ZefirApp::Player(m_EngineContext->resourceManager->GetAnimatedTexture("resources\\anims\\cat.png"), nullptr));
			player->m_Transform2D.SetPosition(200, 200);
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene unload");
		}

		void OnEvent(const SDL_Event& e) 
		{
			player->HandleEvent(e);
			player2->HandleEvent(e);

			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				if (e.key.keysym.sym == SDLK_e)
				{
					m_EngineContext->soundManager->PlaySound(
						m_EngineContext->resourceManager->GetSound("resources\\sounds\\win1.wav")
					);
				}
			}
		}
		
		void Update(double deltaTime) override
		{
			
		}

		void Render(const std::unique_ptr<Zefir::Renderer>& renderer) override
		{
			player->Render(renderer);
			player2->Render(renderer);
			Zefir::RenderText(text, m_EngineContext->renderer, 100, 100);
		}

	private:
		std::unique_ptr<ZefirApp::Player> player = nullptr;
		std::unique_ptr<ZefirApp::Player> player2 = nullptr;
	};
}