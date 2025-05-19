#pragma once

#include <scene/Scene.h>

#include <SDL.h>
#include <memory>

namespace Zefir
{
	class SceneManager
	{
	public:
		SceneManager();

		void LoadScene(std::unique_ptr<Scene> newScene, EngineContext* context);
		void Update(double deltaTime);
		void Render(const std::unique_ptr<Renderer>& renderer);
		void OnEvent(const SDL_Event& e);

	private:
		std::unique_ptr<Scene> m_CurrentScene;
	};
}