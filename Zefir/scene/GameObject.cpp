#include <scene/GameObject.h>

namespace Zefir
{
	GameObject::GameObject()
		: m_Name("Gameobject"), m_Transform2D(), m_Texture(nullptr),
		m_AnimFrameTimer(), m_Rigidbody2D() {}

	GameObject::GameObject(std::string name)
		: m_Name(name), m_Transform2D(), m_Texture(nullptr), 
		m_AnimFrameTimer(), m_Rigidbody2D() { }

	GameObject::GameObject(std::string name, float x, float y)
		: m_Name(name), m_Transform2D(), m_Texture(nullptr),
		m_AnimFrameTimer(), m_Rigidbody2D()
	{
		m_Transform2D.position = { x, y };
	}

	void GameObject::Render(const std::unique_ptr<Renderer>& renderer)
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
		//Debug draw colliders
		SDL_FRect rect = { 
			m_BoxCollider.position.x, m_BoxCollider.position.y,
			m_BoxCollider.size.x, m_BoxCollider.size.y
		};

		SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 0, 255, 0, 255);
		SDL_RenderDrawRectF(renderer->GetSDLRenderer(), &rect);
		SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 255, 255, 255);
#endif
				
	}

	void GameObject::Update(double deltaTime)
	{
		LOG_INFO(m_Name, " has an empty update function called.");
	}

	void GameObject::OnCollide(GameObject& other)
	{
		LOG_INFO(m_Name, "Collided with ", other.m_Name, ".");
	}

	void GameObject::HandleEvent(const SDL_Event& e)
	{
		LOG_WARN("HandleEvent method used but not implemented for GameObject ", m_Name, ".");
	}
}