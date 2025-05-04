#include <GameObject.h>

namespace Zefir
{
	GameObject::GameObject()
		: m_Name("Gameobject"), m_Transform(), m_Velocity(0, 0), m_Texture(nullptr), m_AnimFrameTimer() {
	}

	GameObject::GameObject(std::string name)
		: m_Name(name), m_Transform(), m_Velocity(0, 0), m_Texture(nullptr), m_AnimFrameTimer() { }

	GameObject::GameObject(std::string name, int x, int y)
		: m_Name(name), m_Transform(), m_Velocity(0, 0), m_Texture(nullptr), m_AnimFrameTimer()
	{
		m_Transform.SetPosition(x, y);
	}

	void GameObject::Render(Renderer* renderer)
	{
		static int numberFrame = 0;

		if (m_Texture != nullptr)
		{
			if (m_Texture->IsAnimated())
			{
				AnimatedTexture* ptr_anim = dynamic_cast<AnimatedTexture*>(m_Texture.get());
				
				renderer->RenderAnimFrame(m_Texture->GetSDLTexture(), m_Transform.position, m_Transform.size,
					ptr_anim->GetFrameW(), ptr_anim->GetFrameH(), numberFrame);
				
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
				renderer->RenderStaticTexture(m_Texture->GetSDLTexture(), m_Transform.position, m_Transform.size);
			}
		}
		else
		{
			// GO has no texture, render a filled rect
			renderer->RenderFilledRect(m_Transform.position, m_Transform.size);
		}

		
#ifndef NDEBUG
		//Debug draw colliders
		SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 0, 255, 0, 255);
		SDL_RenderDrawRectF(renderer->GetSDLRenderer(), &m_Transform.collider);
		SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 255, 255, 255);
#endif
				
	}

	void GameObject::Update(double deltaTime)
	{
		Move(deltaTime);
	}

	void GameObject::Move(double deltaTime)
	{
		m_Transform.position += m_Velocity * deltaTime;
		m_Transform.UpdateCollider();
	}

	void GameObject::OnCollide(GameObject& other)
	{
		std::cout << m_Name << "Collided with " << other.m_Name << "." << std::endl;
	}

	void GameObject::HandleEvent(SDL_Event& e)
	{
		std::cerr << "HandleEvent method used but not implemented for GameObject " << m_Name << "." << std::endl;
	}
}