#include <Player.h>
#include <GameConfig.h>

namespace DjipiApp
{
	Player::Player()
	{
		m_Transform.SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_Transform.SetSize(50, 50);
	}

	void Player::Update(double deltaTime)
	{
		GameObject::Move(deltaTime);
	}

	void Player::HandleEvent(SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP) m_VelY -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN) m_VelY += PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_VelX -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_VelX += PLAYER_SPEED;
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP) m_VelY += PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN) m_VelY -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_VelX += PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_VelX -= PLAYER_SPEED;
		}
	}
}