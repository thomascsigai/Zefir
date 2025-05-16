#pragma once

#include <scene/Scene.h>

#include <SDL.h>
#include <memory>

namespace Zefir
{
	class SceneManager
	{
	public:
		SceneManager() : m_CurrentScene(nullptr)
		{

		}

		void LoadScene(std::unique_ptr<Scene> newScene)
		{
			if (m_CurrentScene)
			{
				m_CurrentScene->OnUnload();
			}
			m_CurrentScene = std::move(newScene);
			m_CurrentScene->OnLoad();
		}

		void Update(double deltaTime)
		{
			if (m_CurrentScene)
			{
				m_CurrentScene->Update(deltaTime);
			}
		}

		void Render()
		{
			if (m_CurrentScene)
			{
				m_CurrentScene->Render();
			}
		}

		void OnEvent(const SDL_Event& e)
		{
			if (m_CurrentScene)
			{
				m_CurrentScene->OnEvent(e);
			}
		}

	private:
		std::unique_ptr<Scene> m_CurrentScene;
	};
}