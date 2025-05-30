#include <scene/GameObject.h>

namespace Zefir
{
	GameObject::GameObject()
		: m_Name("Gameobject"), m_Transform2D(), m_Texture(nullptr),
		m_AnimFrameTimer(), m_Rigidbody2D(), m_Collider(nullptr) {}

	GameObject::GameObject(std::string name)
		: m_Name(name), m_Transform2D(), m_Texture(nullptr), 
		m_AnimFrameTimer(), m_Rigidbody2D(), m_Collider(nullptr) { }

	GameObject::GameObject(std::string name, float x, float y)
		: m_Name(name), m_Transform2D(), m_Texture(nullptr),
		m_AnimFrameTimer(), m_Rigidbody2D(), m_Collider(nullptr)
	{
		m_Transform2D.position = { x, y };
	}

	void GameObject::SetupCollider(Vector2 position, Vector2 size)
	{
		m_Collider = std::make_unique<BoxCollider>(position, size);
	}

	void GameObject::SetupCollider(Vector2 position, float radius)
	{
		m_Collider = std::make_unique<CircleCollider>(position, radius);
	}

	void GameObject::Render(Renderer* renderer)
	{
		static int numberFrame = 0;

		if (m_Texture != nullptr)
		{
			if (m_Texture->IsAnimated())
			{
				AnimatedTexture* ptr_anim = dynamic_cast<AnimatedTexture*>(m_Texture.get());
				
				renderer->RenderAnimFrame(m_Texture->GetSDLTexture(), m_Transform2D.position, m_Transform2D.size,
					ptr_anim->GetFrameW(), ptr_anim->GetFrameH(), numberFrame, 0);
				
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
				renderer->RenderStaticTexture(m_Texture->GetSDLTexture(), m_Transform2D.position, m_Transform2D.size, 0);
			}
		}
		else
		{
			// GO has no texture, render a filled rect
			renderer->RenderFilledRect(m_Transform2D.position, m_Transform2D.size);
		}

		
#ifndef NDEBUG
		m_Collider->Render(renderer);
#endif
				
	}
}