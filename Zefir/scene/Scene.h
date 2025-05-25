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

		void AddObjectToScene(std::unique_ptr<GameObject> go);

	public:
		Scene();
		virtual ~Scene() = default;

		virtual void OnLoad() {}
		virtual void OnUnload() {}
		// Events handled by the user in his scene
		virtual void OnSceneEvent(const SDL_Event& e) = 0;

		void OnEvent(const SDL_Event& e);
		void Update(double deltaTime);
		void Render(const std::unique_ptr<Renderer>& renderer);
		void OnAttach(EngineContext* context);
	};
}