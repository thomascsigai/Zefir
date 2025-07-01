#include <scene/GameObject.h>

namespace Zefir
{
	GameObject::GameObject()
		: m_Name("Gameobject"), m_Transform2D(0, 0), m_Texture(nullptr),
		m_AnimFrameTimer(), m_AnimFrameNumber(0), m_AnimEnded(false)
	{
		m_UsePhysics = false;
		m_BodyDef = b2DefaultBodyDef();
		m_BodyId = {};
		m_ShapeDef = b2DefaultShapeDef();
		m_Box = b2MakeBox(0.5f, 0.5f);
	}

	GameObject::GameObject(std::string name)
		: m_Name(name), m_Transform2D(0, 0), m_Texture(nullptr), 
		m_AnimFrameTimer(), m_AnimFrameNumber(0), m_AnimEnded(false)
	{
		m_UsePhysics = false;
		m_BodyDef = b2DefaultBodyDef();
		m_BodyId = {};
		m_ShapeDef = b2DefaultShapeDef();
		m_Box = b2MakeBox(0.5f, 0.5f);
	}

	GameObject::GameObject(std::string name, float x, float y)
		: m_Name(name), m_Transform2D(x, y), m_Texture(nullptr),
		m_AnimFrameTimer(), m_AnimFrameNumber(0), m_AnimEnded(false)
	{
		m_UsePhysics = false;
		m_BodyDef = b2DefaultBodyDef();
		m_BodyId = {};
		m_ShapeDef = b2DefaultShapeDef();
		m_Box = b2MakeBox(0.5f, 0.5f);
	}

	void GameObject::Render(Renderer* renderer, const Camera& cam)
	{
		if (m_Texture != nullptr)
		{
			if (m_Texture->IsAnimated())
			{
				AnimatedTexture* ptr_anim = dynamic_cast<AnimatedTexture*>(m_Texture.get());
				
				renderer->RenderAnimFrame(m_Texture->GetSDLTexture(), m_Transform2D.position, m_Transform2D.size,
					ptr_anim->GetFrameW(), ptr_anim->GetFrameH(), m_AnimFrameNumber, m_Transform2D.rotation, cam,
					m_Transform2D.horizontalFlip, m_Transform2D.verticalFlip);
				
				if (m_AnimFrameTimer.GetTicks() >= ptr_anim->GetFrameTime())
				{
					m_AnimFrameNumber++;

					m_AnimFrameTimer.Stop();
					m_AnimFrameTimer.Start();

					if (m_AnimFrameNumber >= ptr_anim->GetFrameCount())
					{
						if (ptr_anim->IsRepeat())
						{
							m_AnimFrameNumber = 0;
						}
						else
						{
							m_AnimFrameNumber--;
							m_AnimEnded = true;
						}
					}
				}
			}
			else
			{
				renderer->RenderStaticTexture(m_Texture->GetSDLTexture(), m_Transform2D.position,
					m_Transform2D.size, m_Transform2D.rotation, cam, m_Transform2D.horizontalFlip,
					m_Transform2D.verticalFlip);
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