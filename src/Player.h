#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Player : public Zefir::GameObject
	{
	public:
		Player();

		void Update(double deltaTime) override;

		void HandleEvent(SDL_Event& e) override;
	};
}