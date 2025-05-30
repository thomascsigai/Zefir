#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Ground : public Zefir::GameObject
	{
	public:
		Ground(float x, float y) : GameObject("Ground", x, y)
		{
			m_Transform2D.size = { 600, 30 };
			m_Rigidbody2D.type = Zefir::BodyType::Static;

			SetupCollider(m_Transform2D.position, m_Transform2D.size);
		}

		void Update(double deltaTime) override {}
		void HandleEvent(const SDL_Event& e) override {}
	};
}