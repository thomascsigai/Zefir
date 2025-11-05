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
		int m_AnimFrameNumber;

		bool m_AnimEnded;

	public:
		GameObject();
		GameObject(std::string name);
		GameObject(std::string name, float x, float y);

		virtual void Render(Renderer* renderer, const Camera& cam);

		virtual void Update(double deltaTime) = 0;
		virtual void HandleEvent(const SDL_Event& e) = 0;

		virtual void OnCollisionEnter(GameObject* other, b2Manifold manifold) {}
		virtual void OnCollisionExit(GameObject* other) {}

		void RemoveObjectFromScene();

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