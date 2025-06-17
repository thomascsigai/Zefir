#include <scene/GameObject.h>

namespace Zefir
{
	GameObject::GameObject()
		: m_Name("Gameobject"), m_Transform2D(), m_Texture(nullptr),
		m_AnimFrameTimer()
	{
		m_UsePhysics = false;
		m_BodyDef = b2DefaultBodyDef();
		m_BodyId = {};
		m_ShapeDef = b2DefaultShapeDef();
		m_Box = b2MakeBox(0.5f, 0.5f);
	}

	GameObject::GameObject(std::string name)
		: m_Name(name), m_Transform2D(), m_Texture(nullptr), 
		m_AnimFrameTimer()
	{
		m_UsePhysics = false;
		m_BodyDef = b2DefaultBodyDef();
		m_BodyId = {};
		m_ShapeDef = b2DefaultShapeDef();
		m_Box = b2MakeBox(0.5f, 0.5f);
	}

	GameObject::GameObject(std::string name, float x, float y)
		: m_Name(name), m_Transform2D(), m_Texture(nullptr),
		m_AnimFrameTimer()
	{
		m_Transform2D.position = { x, y };

		m_UsePhysics = false;
		m_BodyDef = b2DefaultBodyDef();
		m_BodyId = {};
		m_ShapeDef = b2DefaultShapeDef();
		m_Box = b2MakeBox(0.5f, 0.5f);
	}

	void GameObject::Render(Renderer* renderer, const Camera& cam)
	{
		static int numberFrame = 0;

		if (m_Texture != nullptr)
		{
			if (m_Texture->IsAnimated())
			{
				AnimatedTexture* ptr_anim = dynamic_cast<AnimatedTexture*>(m_Texture.get());
				
				renderer->RenderAnimFrame(m_Texture->GetSDLTexture(), m_Transform2D.position, m_Transform2D.size,
					ptr_anim->GetFrameW(), ptr_anim->GetFrameH(), numberFrame, m_Transform2D.rotation, cam);
				
				if (m_AnimFrameTimer.GetTicks() >= ptr_anim->GetFrameTime())
				{
					numberFrame++;
					m_AnimFrameTimer.Stop();
					m_AnimFrameTimer.Start();

					if (numberFrame >= ptr_anim->GetFrameCount())
					{
						numberFrame = 0;
					}
				}
			}
			else
			{
				renderer->RenderStaticTexture(m_Texture->GetSDLTexture(), m_Transform2D.position,
					m_Transform2D.size, m_Transform2D.rotation, cam);
			}
		}
		else
		{
			// GO has no texture, render a filled rect
			renderer->RenderFilledRect(m_Transform2D.position, m_Transform2D.size, cam);
		}

		
#ifndef NDEBUG
		// Draw collider

		if (m_UsePhysics)
		{
			SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 0, 0, 255);
			Vector2 pos = Vector2(b2Body_GetPosition(m_BodyId).x, b2Body_GetPosition(m_BodyId).y);
			renderer->RenderRect(pos, m_Transform2D.size, cam);
			SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 255, 255, 255);
		}
#endif
				
	}
}