#include <Player.h>
#include <GameConfig.h>

namespace ZefirApp
{
	Player::Player(std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk)
		: GameObject("Player"), m_IdleTexture(idle), m_WalkTexture(walk)
	{
		m_Transform.SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_Transform.SetSize(100, 106);

		SetTexture(m_IdleTexture);
	}

	void Player::Update(double deltaTime)
	{
		GameObject::Move(deltaTime);

		if (m_Velocity.x != 0 || m_Velocity.y != 0)
		{
			if (m_WalkTexture != m_Texture)
				SetTexture(m_WalkTexture);
		}
		else
		{
			SetTexture(m_IdleTexture);
		}
	}

	void Player::HandleEvent(SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP) m_Velocity.y -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN) m_Velocity.y += PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_Velocity.x -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_Velocity.x += PLAYER_SPEED;
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP) m_Velocity.y += PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN) m_Velocity.y -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_Velocity.x += PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_Velocity.x -= PLAYER_SPEED;
		}
	}
}