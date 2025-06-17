#pragma once

#include <SDL.h>
#include <box2d/box2d.h>
#include <iostream>

#include <scene/Transform2D.h>
#include <resource/types/Texture.h>
#include <resource/types/AnimatedTexture.h>
#include <core/time/Timer.h>
#include <scene/Camera.h>

namespace Zefir
{
	class GameObject
	{

	public:
		std::string m_Name;
		Transform2D m_Transform2D;
		
		bool m_UsePhysics;
		b2BodyDef m_BodyDef;
		b2BodyId m_BodyId;
		b2ShapeDef m_ShapeDef;
		b2Polygon m_Box;

	protected:
		std::shared_ptr<Texture> m_Texture;
		Timer m_AnimFrameTimer;

	public:
		GameObject();
		GameObject(std::string name);
		GameObject(std::string name, float x, float y);

		// Setup a AABB collider for the Go
		void SetupCollider(Vector2 position, Vector2 size);
		// Setup a Circle collider for the Go
		void SetupCollider(Vector2 position, float radius);

		virtual void Render(Renderer* renderer, const Camera& cam);

		virtual void Update(double deltaTime) = 0;
		virtual void HandleEvent(const SDL_Event& e) = 0;

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