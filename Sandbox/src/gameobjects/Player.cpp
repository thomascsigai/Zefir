#include <gameobjects/Player.h>
#include <GameConfig.h>

namespace ZefirApp
{
	Player::Player(std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk)
		: GameObject("Player"), m_IdleTexture(idle), m_WalkTexture(walk)
	{
		m_Transform2D.SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		m_Transform2D.SetSize(100, 106);

		m_Rigidbody2D.useGravity = false;
		m_BoxCollider.size = { 100, 106 };

		SetTexture(m_IdleTexture);
	}

	void Player::Update(double deltaTime)
	{
		if (m_Rigidbody2D.velocity.x != 0 || m_Rigidbody2D.velocity.y != 0)
		{
			if (m_WalkTexture != m_Texture)
				SetTexture(m_WalkTexture);
		}
		else
		{
			SetTexture(m_IdleTexture);
		}
	}

	void Player::HandleEvent(const SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP)		m_Rigidbody2D.AddForce({ 0, -PLAYER_SPEED });
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN)		m_Rigidbody2D.AddForce({ 0, PLAYER_SPEED });
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT)		m_Rigidbody2D.AddForce({ -PLAYER_SPEED, 0 });
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT)		m_Rigidbody2D.AddForce({ PLAYER_SPEED, 0 });
		}
	}
}