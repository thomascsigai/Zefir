#pragma once

#include <SDL.h>
#include <Vector2.h>

namespace Djipi
{
	struct Transform2D
	{
		Vector2 position = Vector2(0, 0);
		Vector2 size = Vector2(0, 0);

		SDL_FRect collider = {};

		void SetPosition(float _x, float _y)
		{
			position = Vector2(_x, _y);
			UpdateCollider();
		}
		
		void SetPosition(Vector2 _position)
		{
			position = _position;
			UpdateCollider();
		}

		void SetSize(float _w, float _h)
		{
			size = Vector2(_w, _h);
			UpdateCollider();
		}

		void UpdateCollider() 
		{ 
			collider = { position.x, position.y, size.x, size.y }; 
		}
	};
}