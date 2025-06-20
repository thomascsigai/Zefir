#include <scene/Scene.h>

namespace Zefir
{
	Scene::Scene()
	{
		m_EngineContext = nullptr;
		m_SceneObjects.reserve(10);

		m_WorldDef = b2DefaultWorldDef();
		m_WorldDef.gravity = { 0.0f, -10.0f };
		m_WorldId = b2CreateWorld(&m_WorldDef);

		m_Cam = Camera();
	}

	Scene::~Scene()
	{
		b2DestroyWorld(m_WorldId);
	}

	void Scene::OnEvent(const SDL_Event& e)
	{
		if (e.type == EngineEvents::CAMERA_MOVE)
		{
			Vector2 *newPos = static_cast<Vector2*>(e.user.data1);
			m_Cam.position = *newPos;
			delete(newPos);
		}

		if (e.type == EngineEvents::CAMERA_ZOOM)
		{
			double *newZoom = static_cast<double*>(e.user.data1);
			m_Cam.zoom = *newZoom;
			delete newZoom;
		}

		for (std::unique_ptr<GameObject>& go : m_SceneObjects)
		{
			go->HandleEvent(e);
		}
		OnSceneEvent(e);
	}

	void Scene::Update(double deltaTime)
	{
		// Update the scene
		OnUpdate();

		// Update physics
		accumulator += deltaTime;
		while (accumulator >= TIME_STEP)
		{
			for (auto& go : m_SceneObjects)
			{
				if (go->m_UsePhysics)
					go->m_Transform2D.oldPosition = Vector2(b2Body_GetPosition(go->m_BodyId).x, b2Body_GetPosition(go->m_BodyId).y); // ajouter ce champ
			}

			b2World_Step(m_WorldId, TIME_STEP, 4);
			accumulator -= TIME_STEP;
		}

		// Update all gameobjects
		float alpha = static_cast<float>(accumulator / TIME_STEP);

		for (std::unique_ptr<GameObject>& go : m_SceneObjects)
		{
			go->Update(deltaTime);

			if (go->m_UsePhysics)
			{
				b2Vec2 currPos = b2Body_GetPosition(go->m_BodyId);
				Vector2 interpolatedPos = go->m_Transform2D.oldPosition * (1.0f - alpha) + currPos * alpha;

				go->m_Transform2D.SetPosition(interpolatedPos);

				go->m_Transform2D.SetRotation(
					-b2Rot_GetAngle(b2Body_GetRotation(go->m_BodyId))
				);
			}
		}
	}

	void Scene::Render(Renderer* renderer)
	{
		for (std::unique_ptr<GameObject>& go : m_SceneObjects)
		{
			go->Render(renderer, m_Cam);
		}

#ifndef NDEBUG
		renderer->RenderDebugAxis(m_Cam);
#endif
	}

	void Scene::OnAttach(EngineContext* context)
	{ 
		m_EngineContext = context;
	}

	void Scene::AddObjectToScene(std::unique_ptr<GameObject> go)
	{
		if (go->m_UsePhysics)
		{
			go->m_BodyId = b2CreateBody(m_WorldId, &go.get()->m_BodyDef);
			b2CreatePolygonShape(go->m_BodyId, &go->m_ShapeDef, &go->m_Box);
		}

		m_SceneObjects.push_back(std::move(go));
	}
}