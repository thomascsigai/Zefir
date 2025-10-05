#include <scene/Scene.h>

namespace Zefir
{
	Scene::Scene()
	{
		m_EngineContext = nullptr;
		m_SceneObjects.reserve(10);

		m_WorldDef = b2DefaultWorldDef();
		m_WorldDef.gravity = { 0.0f, -30.0f };
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

		if (e.type == EngineEvents::SCENE_REMOVE_OBJECT)
		{
			int* objectId = static_cast<int*>(e.user.data1);
			RemoveObject(*objectId);
			delete objectId;
		}

		for (auto& go : m_SceneObjects)
		{
			go.second->HandleEvent(e);
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
				if (go.second->m_UsePhysics)
					go.second->m_Transform2D.oldPosition = Vector2(
						b2Body_GetPosition(go.second->m_BodyId).x,
						b2Body_GetPosition(go.second->m_BodyId).y
					); 
			}

			b2World_Step(m_WorldId, TIME_STEP, 4);
			b2ContactEvents contactEvents = b2World_GetContactEvents(m_WorldId);
			for (int i = 0; i < contactEvents.beginCount; ++i)
			{
				b2ContactBeginTouchEvent* e = contactEvents.beginEvents + i;

				m_SceneObjects[e->shapeIdA.index1]->OnCollisionEnter(m_SceneObjects[e->shapeIdB.index1].get(), e->manifold);
				e->manifold.normal = -e->manifold.normal;
				m_SceneObjects[e->shapeIdB.index1]->OnCollisionEnter(m_SceneObjects[e->shapeIdA.index1].get(), e->manifold);
			}

			for (int i = 0; i < contactEvents.endCount; ++i)
			{
				b2ContactEndTouchEvent* e = contactEvents.endEvents + i;
				if (b2Shape_IsValid(e->shapeIdA) && b2Shape_IsValid(e->shapeIdB))
				{
					m_SceneObjects[e->shapeIdA.index1]->OnCollisionExit(m_SceneObjects[e->shapeIdB.index1].get());
					m_SceneObjects[e->shapeIdB.index1]->OnCollisionExit(m_SceneObjects[e->shapeIdA.index1].get());
				}
			}

			for (int i = 0; i < contactEvents.hitCount; ++i) {
				auto* hitEvent = contactEvents.hitEvents + i;
			}

			accumulator -= TIME_STEP;
		}


		// Update all gameobjects
		float alpha = static_cast<float>(accumulator / TIME_STEP);

		for (auto& go : m_SceneObjects)
		{
			go.second->Update(deltaTime);

			if (go.second->m_UsePhysics)
			{
				b2Vec2 currPos = b2Body_GetPosition(go.second->m_BodyId);
				Vector2 interpolatedPos = go.second->m_Transform2D.oldPosition * (1.0f - alpha) + currPos * alpha;

				go.second->m_Transform2D.SetPosition(interpolatedPos);

				go.second->m_Transform2D.SetRotation(
					-b2Rot_GetAngle(b2Body_GetRotation(go.second->m_BodyId))
				);
			}
		}

		// Update UI
		for (auto& ui_obj : m_UIObjects)
		{
			ui_obj.second->Update();
		}
	}

	void Scene::Render(Renderer* renderer)
	{
		// Render Gameobjects
		for (auto& go : m_SceneObjects)
		{
			go.second->Render(renderer, m_Cam);
		}

		//Render UI
		for (auto& ui_obj : m_UIObjects)
		{
			ui_obj.second->Render(renderer, m_Cam);
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

		m_SceneObjects[go->m_BodyId.index1] = std::move(go);
	}

	void Scene::RemoveObject(int objectId)
	{
		if (m_SceneObjects.contains(objectId))
		{
			b2DestroyBody(m_SceneObjects[objectId]->m_BodyId);
			m_SceneObjects.erase(objectId);
		}
		else
		{
			LOG_WARN("Trying to remove an object that does not exist.");
		}
	}

	void Scene::AddUIToScene(std::unique_ptr<UIObject> ui_obj)
	{
		static int id = 0;
		ui_obj->m_Id = id;
		m_UIObjects[id] = std::move(ui_obj);
		id++;
	}
	
	void Scene::RemoveUI(int ui_objID)
	{
		if (m_UIObjects.contains(ui_objID))
		{
			m_UIObjects.erase(ui_objID);
		}
		else
		{
			LOG_WARN("Trying to remove a UI object that does not exist.");
		}
	}
}