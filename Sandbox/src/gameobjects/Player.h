#pragma once

#include <Zefir.h>

namespace ZefirApp
{
	class Player : public Zefir::GameObject
	{
	public:
		Player(std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk);

		void Update(double deltaTime) override;

		void HandleEvent(const SDL_Event& e) override;

	private:
		std::shared_ptr<Zefir::Texture> m_IdleTexture;
		std::shared_ptr<Zefir::Texture> m_WalkTexture;
	};
}