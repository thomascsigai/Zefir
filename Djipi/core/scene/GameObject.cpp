#include <GameObject.h>

namespace Djipi
{
	GameObject::GameObject(std::shared_ptr<Texture> texture)
		: m_Name("GameObject"), m_Velocity(0, 0), m_Texture(texture) { }

	GameObject::GameObject(std::string name, std::shared_ptr<Texture> texture)
		: m_Name(name), m_Velocity(0, 0), m_Texture(texture) { }

	GameObject::GameObject(std::string name, int x, int y, std::shared_ptr<Texture> texture)
		: m_Name(name), m_Velocity(0, 0), m_Texture(texture)
	{
		m_Transform.SetPosition(x, y);
	}

	void GameObject::Render(SDL_Renderer* renderer)
	{
		if (m_Texture == nullptr)
		{
			SDL_FRect rect = {
		m_Transform.position.x, m_Transform.position.y,
		m_Transform.size.x, m_Transform.size.y
			};
			SDL_RenderFillRectF(renderer, &rect);
		}
		else
		{
			SDL_Rect rect = {
		m_Transform.position.x, m_Transform.position.y,
		m_Transform.size.x, m_Transform.size.y
			};
			SDL_RenderCopy(renderer, m_Texture->GetSDLTexture(), NULL, &rect);
		}
		
#ifndef NDEBUG
		//Debug draw colliders
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		SDL_RenderDrawRectF(renderer, &m_Transform.collider);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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