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
			go->m_Transform2D.SetPosition(
				b2Body_GetPosition(go->m_BodyId).x, 
				b2Body_GetPosition(go->m_BodyId).y
			);
			go->m_Transform2D.SetRotation(
				-b2Rot_GetAngle(b2Body_GetRotation(go->m_BodyId))
			);
		}
		b2World_Step(m_WorldId, deltaTime, 4);
	}

	void Scene::Render(Renderer* renderer)
	{

#ifndef NDEBUG
		renderer->RenderDebugAxis(m_Cam);
#endif

		for (std::unique_ptr<GameObject>& go : m_SceneObjects)
		{
			go->Render(renderer, m_Cam);
		}
	}

	void Scene::OnAttach(EngineContext* context)
	{ 
		m_EngineContext = context;
	}

	void Scene::AddObjectToScene(std::unique_ptr<GameObject> go)
	{
		go->m_BodyId = b2CreateBody(m_WorldId, &go.get()->m_BodyDef);
		b2CreatePolygonShape(go->m_BodyId, &go->m_ShapeDef, &go->m_Box);
		m_SceneObjects.push_back(std::move(go));
	}
}