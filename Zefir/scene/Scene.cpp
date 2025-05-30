#include <scene/Scene.h>

namespace Zefir
{
	Scene::Scene()
	{
		m_EngineContext = nullptr;
		m_SceneObjects.reserve(10);
		m_PhysicsWorld = std::make_unique<PhysicsWorld>();
	}

	void Scene::OnEvent(const SDL_Event& e)
	{
		for (std::unique_ptr<GameObject>& go : m_SceneObjects)
		{
			go->HandleEvent(e);
		}
		OnSceneEvent(e);
	}

	void Scene::Update(double deltaTime)
	{
		for (std::unique_ptr<GameObject>& go : m_SceneObjects)
		{
			go->Update(deltaTime);
		}
		m_PhysicsWorld->Step(deltaTime);
	}

	void Scene::Render(Renderer* renderer)
	{
		for (std::unique_ptr<GameObject>& go : m_SceneObjects)
		{
			go->Render(renderer);
		}
	}

	void Scene::OnAttach(EngineContext* context) { m_EngineContext = context; }

	void Scene::AddObjectToScene(std::unique_ptr<GameObject> go)
	{
		m_SceneObjects.push_back(std::move(go));
		m_PhysicsWorld->AddObject(m_SceneObjects.back().get());
	}
}