#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Ground : public Zefir::GameObject
	{
	public:
		Ground(float x, float y) : GameObject("Ground", x, y)
		{
			m_Transform2D.size = { 16, 1 };
			m_BodyDef.position = { x, y };
			m_Box = b2MakeBox(8.0f, 0.5f);
		}
		~Ground() = default;

		void Update(double deltaTime) override {}
		void HandleEvent(const SDL_Event& e) override {}
	};
}