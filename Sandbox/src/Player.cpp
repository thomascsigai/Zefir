#include <Player.h>
#include <GameConfig.h>

namespace ZefirApp
{
	Player::Player(int x, int y, std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk)
		: GameObject("Player", x, y), m_IdleTexture(idle), m_WalkTexture(walk)
	{
		//m_Transform.SetPosition(SCREEN_WIDTH / 2, 0);
		m_Transform2D.size = { 50, 53 };
		
		m_BoxCollider.position = m_Transform2D.position;
		m_BoxCollider.size = { 50, 53 };

		m_Rigidbody2D.type = Zefir::BodyType::Dynamic;
		m_Rigidbody2D.useGravity = true;

		SetTexture(m_IdleTexture);
	}

	void Player::Update(double deltaTime)
	{
	}

	void Player::HandleEvent(SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP) m_Rigidbody2D.AddForce({ 100000, -PLAYER_SPEED * 2000 });
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN) m_Rigidbody2D.AddForce({ 0, PLAYER_SPEED });
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_Rigidbody2D.AddForce({ -PLAYER_SPEED, 0 });
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_Rigidbody2D.AddForce({ PLAYER_SPEED, 0 });
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP) m_Rigidbody2D.AddForce({ 0, -PLAYER_SPEED });
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN) m_Rigidbody2D.AddForce({ 0, PLAYER_SPEED });
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_Rigidbody2D.AddForce({ -PLAYER_SPEED, 0 });
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_Rigidbody2D.AddForce({ PLAYER_SPEED, 0 });
		}
	}
}