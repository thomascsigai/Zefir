#include <gameobjects/PhysicObject.h>
#include <GameConfig.h>

namespace ZefirApp
{
	PhysicObject::PhysicObject(float x, float y, std::shared_ptr<Zefir::Texture> texture)
		: GameObject("Physic Object")
	{
		m_Transform2D.SetPosition(x, y);
		m_Transform2D.SetSize(1, 1);

		SetTexture(texture);

		m_UsePhysics = true;
		m_BodyDef.type = b2_dynamicBody;
		m_BodyDef.position = { x, y };
		m_ShapeDef.material.friction = 0.3f;
		m_Box = b2MakeBox(0.5f, 0.5f);
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