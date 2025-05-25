#include <gameobjects/PhysicObject.h>
#include <GameConfig.h>

namespace ZefirApp
{
	PhysicObject::PhysicObject(float x, float y)
		: GameObject("Physic Object")
	{
		m_Transform2D.SetPosition(x, y);
		m_Transform2D.SetSize(50, 53);

		m_Rigidbody2D.type = Zefir::BodyType::Dynamic;

		m_BoxCollider.position = m_Transform2D.position;
		m_BoxCollider.size = { 50, 53 };
	}

	void PhysicObject::Update(double deltaTime)
	{
	}

	void PhysicObject::HandleEvent(const SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.UP) m_Transform2D.position.y -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.DOWN) m_Transform2D.position.y += PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_Transform2D.position.x -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_Transform2D.position.x += PLAYER_SPEED;
		}
	}
}