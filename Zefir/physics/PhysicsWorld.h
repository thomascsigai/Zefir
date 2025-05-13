#pragma once

#include <core/debug/Log.h>
#include <vector>

namespace Zefir
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld()
		{
			if (!Init())
			{
				LOG_WARN("Physics engine not initialized.");
			}
		}
		~PhysicsWorld()
		{
			Shutdown();
		}

		void Step(double deltaTime)
		{
			ApplyGravity();

			for (auto* obj : m_Objects)
			{
				Rigidbody2D& rb = obj->m_Rigidbody2D;
				if (rb.type != BodyType::Dynamic) continue;

				rb.velocity += rb.acceleration * deltaTime * 0.5f;
				obj->m_Transform2D.position += rb.velocity * deltaTime;
				rb.velocity += rb.acceleration * deltaTime * 0.5f;
				rb.acceleration = { 0, 0 };

				obj->m_BoxCollider.position = obj->m_Transform2D.position;

				for (auto* other : m_Objects)
				{
					if (other == obj || other->m_Rigidbody2D.type != BodyType::Static)
						continue;

					const auto& otherCol = other->m_BoxCollider;
					auto& objCol = obj->m_BoxCollider;

					if (CheckCollisionAABB(objCol, otherCol))
					{
						if (rb.velocity.y > 0)
						{
							float penetration = (objCol.position.y + objCol.size.y) - otherCol.position.y;
							obj->m_Transform2D.position.y -= penetration;
							rb.velocity.y = 0;
							rb.acceleration.y = 0;
							objCol.position.y = obj->m_Transform2D.position.y;
						}
					}
				}
			}
			
		}

		void AddObject(GameObject* go)
		{
			m_Objects.push_back(go);
		}

	private:
		std::vector<GameObject*> m_Objects;

		bool Init()
		{
			return true;
		}

		void Shutdown()
		{
		}

		void ApplyGravity()
		{
			for (auto* obj : m_Objects)
			{
				Rigidbody2D& rb = obj->m_Rigidbody2D;
				if (rb.type != BodyType::Dynamic) continue;

				if (rb.useGravity)
				{
					rb.AddForce(GRAVITY_FORCE);
				}
			}
		}

		bool CheckCollisionAABB(const BoxCollider& a, const BoxCollider& b)
		{
			return (
				a.position.x < b.position.x + b.size.x &&
				a.position.x + a.size.x > b.position.x &&
				a.position.y < b.position.y + b.size.y &&
				a.position.y + a.size.y > b.position.y
				);
		}
	};
}