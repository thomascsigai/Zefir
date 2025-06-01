#pragma once

#include <renderer/Renderer.h>

namespace Zefir
{
	struct CollisionPoints {
		Vector2 A; // Furthest point of A into B
		Vector2 B; // Furthest point of B into A
		Vector2 Normal; // B – A normalized
		float Depth;    // Length of B – A
		bool HasCollision;
	};

	struct Collider
	{
		virtual void Render(Renderer* renderer) = 0;


	};

	struct CircleCollider : public Collider
	{
		float radius;
		Vector2 position;

		CircleCollider(Vector2 _position, float _radius)
			: position(_position), radius(_radius) {}

		void Render(Renderer* renderer) override
		{
			SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 0, 255, 0, 255);
			renderer->RenderCircle(position, radius);
			SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 255, 255, 255);
		}
	};

	struct BoxCollider : public Collider
	{
		Vector2 position;
		Vector2 size;

		BoxCollider(Vector2 _position, Vector2 _size)
			: position(_position), size(_size) {}

		void Render(Renderer* renderer) override
		{
			SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 0, 255, 0, 255);
			renderer->RenderRect(position, size);
			SDL_SetRenderDrawColor(renderer->GetSDLRenderer(), 255, 255, 255, 255);
		}

		// AABB collision check
		bool CheckCollision(const BoxCollider& other)
		{
			return (
				position.x < other.position.x + other.size.x &&
				position.x + size.x > other.position.x &&
				position.y < other.position.y + other.size.y &&
				position.y + size.y > other.position.y
				);
		}
	};
}