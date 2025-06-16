#pragma once

#include <core/EngineContext.h>
#include <core/EngineEvents.h>
#include <scene/GameObject.h>
#include <scene/Camera.h>

#include <box2d/box2d.h>

namespace Zefir
{
	class Scene
	{
	protected:
		EngineContext* m_EngineContext;
		std::vector<std::unique_ptr<GameObject>> m_SceneObjects;
		b2WorldDef m_WorldDef;
		b2WorldId m_WorldId;

		Camera m_Cam;

		void AddObjectToScene(std::unique_ptr<GameObject> go);

	public:
		Scene();
		~Scene();


		virtual void OnLoad() = 0;
		virtual void OnUnload() = 0;
		virtual void OnUpdate() = 0;
		// Events handled by the user in his scene
		virtual void OnSceneEvent(const SDL_Event& e) = 0;

		void OnEvent(const SDL_Event& e);
		void Update(double deltaTime);
		void Render(Renderer* renderer);
		void OnAttach(EngineContext* context);

	private:
		// PHYSICS RELATED ATTRIBUTES
		double accumulator = 0.0f;
		double TIME_STEP = 1.0f / 60.0f;
	};
}