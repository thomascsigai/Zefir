#pragma once

#include <SDL.h>
#include <Transform2D.h>
#include <Texture.h>
#include <AnimatedTexture.h>
#include <Timer.h>
#include <Rigidbody2D.h>
#include <BoxCollider.h>

#include <iostream>

namespace Zefir
{
	class GameObject
	{

	public:
		std::string m_Name;
		Transform2D m_Transform2D;
		Rigidbody2D m_Rigidbody2D;
		BoxCollider m_BoxCollider;

	protected:
		std::shared_ptr<Texture> m_Texture;
		Timer m_AnimFrameTimer;

	public:
		GameObject();
		GameObject(std::string name);
		GameObject(std::string name, float x, float y);

		virtual void Render(Renderer* renderer);
		virtual void Update(double deltaTime);
		virtual void OnCollide(GameObject& other);
		virtual void HandleEvent(SDL_Event& e);

		// Getters

		//Setters
		void SetTexture(std::shared_ptr<Texture> texture) 
		{ 
			m_Texture = texture; 

			if (m_Texture != nullptr) {
				if (m_Texture.get()->IsAnimated())
				{
					m_AnimFrameTimer.Start();
				}
			}
		}
	};
}