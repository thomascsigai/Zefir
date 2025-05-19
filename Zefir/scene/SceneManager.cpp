#include <scene/SceneManager.h>

namespace Zefir
{
	SceneManager::SceneManager() : m_CurrentScene(nullptr)
	{

	}

	void SceneManager::LoadScene(std::unique_ptr<Scene> newScene, EngineContext* context)
	{
		if (m_CurrentScene)
		{
			m_CurrentScene->OnUnload();
		}
		newScene->OnAttach(context);
		m_CurrentScene = std::move(newScene);
		m_CurrentScene->OnLoad();
	}

	void SceneManager::Update(double deltaTime)
	{
		if (m_CurrentScene)
		{
			m_CurrentScene->Update(deltaTime);
		}
	}

	void SceneManager::Render(const std::unique_ptr<Renderer>& renderer)
	{
		if (m_CurrentScene)
		{
			m_CurrentScene->Render(renderer);
		}
	}

	void SceneManager::OnEvent(const SDL_Event& e)
	{
		if (m_CurrentScene)
		{
			m_CurrentScene->OnEvent(e);
		}
	}
}