#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class PhysicObject : public Zefir::GameObject
	{
	public:
		PhysicObject(float x, float y);

		void Update(double deltaTime) override;

		void HandleEvent(const SDL_Event& e) override;
	};
}