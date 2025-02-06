#pragma once

#include <iostream>

#include <SDL.h>
#include <Transform.h>

using namespace std;

namespace Djipi
{
	class GameObject
	{
	protected:
		string m_Name;
		Transform m_Transform;
		int m_VelX = 0, m_VelY = 0;

	public:
		GameObject() {}
		GameObject(string name) : m_Name(name) {}
		GameObject(string name, int x, int y) { m_Transform.x = x; m_Transform.y = y; }

		virtual void Render(SDL_Renderer* renderer)
		{
			SDL_FRect rect = { m_Transform.x, m_Transform.y, m_Transform.w, m_Transform.h };
			SDL_RenderFillRectF(renderer, &rect);


			//Debug draw collider
			/*SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawRectF(renderer, &transform.collider);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);*/
		}

		virtual void Update(double deltaTime)
		{
			Move(deltaTime);
		}

		virtual void Move(double deltaTime)
		{
			m_Transform.x += m_VelX * deltaTime;
			m_Transform.y += m_VelY * deltaTime;

			m_Transform.UpdateCollider();
		}

		virtual void OnCollide(GameObject& other)
		{
			cout << m_Name << "Collided with " << other.m_Name << "." << endl;
		}

		virtual void HandleEvent(SDL_Event& e)
		{
			cerr << "HandleEvent method used but not implemented for GameObject " << m_Name << "." << endl;
		}


		// Getters
		Transform GetTransform() const { return m_Transform; }
		string GetName() const { return m_Name; }
		SDL_FRect GetCollider() const { return m_Transform.collider; }

		//Setters
		void SetName(string name) { m_Name = name; }
	};
}