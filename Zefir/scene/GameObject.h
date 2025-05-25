#pragma once

#include <SDL.h>
#include <scene/Transform2D.h>
#include <resource/types/Texture.h>
#include <resource/types/AnimatedTexture.h>
#include <core/time/Timer.h>
#include <physics/Rigidbody2D.h>
#include <physics/BoxCollider.h>

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

		virtual void Render(const std::unique_ptr<Renderer>& renderer);

		virtual void Update(double deltaTime) = 0;
		virtual void HandleEvent(const SDL_Event& e) = 0;

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