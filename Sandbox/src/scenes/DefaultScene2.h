#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>
#include <gameobjects/Player.h>

namespace ZefirApp
{
	class DefaultScene2 : public Zefir::Scene
	{
		void OnLoad() override
		{
			APP_LOG_INFO("Scene 2 load");
			Zefir::LoadText(text, "Scene 2", 50, m_EngineContext->resourceManager, m_EngineContext->renderer, { 255, 255, 255, 255 });
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene 2 unload");
		}

		void Update(double deltaTime) override
		{
			
		}

		void Render(const std::unique_ptr<Zefir::Renderer>& renderer) override
		{
			Zefir::RenderText(text, m_EngineContext->renderer, 100, 100);
		}

		void OnEvent(const SDL_Event& e) 
		{
		}
	};
}