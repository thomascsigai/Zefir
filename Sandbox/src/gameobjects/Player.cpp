#include <gameobjects/Player.h>
#include <GameConfig.h>

namespace ZefirApp
{
	Player::Player(std::shared_ptr<Zefir::Texture> idle, std::shared_ptr<Zefir::Texture> walk)
		: GameObject("Player"), m_IdleTexture(idle), m_WalkTexture(walk)
	{
		m_Transform2D.SetPosition(0, 0);
		m_Transform2D.SetSize(2, 2);

		SetTexture(m_IdleTexture);

		m_BodyDef.type = b2_dynamicBody;
		m_BodyDef.position = { 0, 0 };
		m_BodyDef.gravityScale = 0;
		m_ShapeDef.material.friction = 1.0f;
		m_Box = b2MakeBox(0.5f, 0.5f);
	}

	void Player::Update(double deltaTime)
	{
		/*if (m_Rigidbody2D.velocity.x != 0 || m_Rigidbody2D.velocity.y != 0)
		{
			if (m_WalkTexture != m_Texture)
				SetTexture(m_WalkTexture);
		}
		else
		{
			SetTexture(m_IdleTexture);
		}*/
	}

	void Player::HandleEvent(const SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP)	b2Body_ApplyForceToCenter(m_BodyId, { 0, PLAYER_SPEED }, true);
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN)	b2Body_ApplyForceToCenter(m_BodyId, { 0, -PLAYER_SPEED }, true);
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT)	b2Body_ApplyForceToCenter(m_BodyId, { -PLAYER_SPEED, 0 }, true);
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT)	b2Body_ApplyForceToCenter(m_BodyId, { PLAYER_SPEED, 0 }, true);
			
		}
		if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP)	b2Body_ApplyForceToCenter(m_BodyId, { 0, -PLAYER_SPEED }, true);
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN)	b2Body_ApplyForceToCenter(m_BodyId, { 0, PLAYER_SPEED }, true);
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT)	b2Body_ApplyForceToCenter(m_BodyId, { PLAYER_SPEED, 0 }, true);
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT)	b2Body_ApplyForceToCenter(m_BodyId, { -PLAYER_SPEED, 0 }, true);
		}
	}
}