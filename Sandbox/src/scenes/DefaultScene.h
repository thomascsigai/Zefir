#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>
#include <Player.h>

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
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene unload");
		}

		void OnEvent(const SDL_Event& e) 
		{
			player->HandleEvent(e);
		}
		
		void Update(double deltaTime) override
		{
			
		}

		void Render(const std::unique_ptr<Zefir::Renderer>& renderer) override
		{
			player->Render(renderer);
			Zefir::RenderText(text, m_EngineContext->renderer, 100, 100);
		}

	private:
		std::unique_ptr<ZefirApp::Player> player = nullptr;
	};
}