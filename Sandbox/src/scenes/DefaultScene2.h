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
		}

		void OnUnload() override
		{
			APP_LOG_INFO("Scene 2 unload");
		}

		void OnSceneEvent(const SDL_Event& e)
		{
		}
	};
}