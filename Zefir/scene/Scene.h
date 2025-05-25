#pragma once

#include <core/EngineContext.h>
#include <scene/GameObject.h>
#include <physics/PhysicsWorld.h>

namespace Zefir
{
	class Scene
	{
	protected:
		EngineContext* m_EngineContext;
		std::vector<std::unique_ptr<GameObject>> m_SceneObjects;
		std::unique_ptr<PhysicsWorld> m_PhysicsWorld;

		void AddObjectToScene(std::unique_ptr<GameObject> go)
		{
			m_SceneObjects.push_back(std::move(go));
			m_PhysicsWorld->AddObject(m_SceneObjects.back().get());
		}

	public:
		Scene()
		{
			m_EngineContext = nullptr;
			m_SceneObjects.reserve(10);
			m_PhysicsWorld = std::make_unique<PhysicsWorld>();
		}

		virtual ~Scene() = default;
		virtual void OnLoad() {}
		virtual void OnUnload() {}
		virtual void OnEvent(const SDL_Event& e) {}

		void Update(double deltaTime)
		{
			for (std::unique_ptr<GameObject>& go : m_SceneObjects)
			{
				go->Update(deltaTime);
			}
			m_PhysicsWorld->Step(deltaTime);
		}

		void Render(const std::unique_ptr<Renderer>& renderer)
		{
			for (std::unique_ptr<GameObject>& go : m_SceneObjects)
			{
				go->Render(renderer);
			}
		}

		void OnAttach(EngineContext* context) { m_EngineContext = context; }
	};
}