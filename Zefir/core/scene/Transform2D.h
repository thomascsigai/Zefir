#pragma once

#include <SDL.h>
#include <Vector2.h>

namespace Zefir
{
	struct Transform2D
	{
		Vector2 position = Vector2(0, 0);
		Vector2 size = Vector2(0, 0);

		void SetPosition(float _x, float _y)
		{
			position = Vector2(_x, _y);
		}
		
		void SetPosition(Vector2 _position)
		{
			position = _position;
		}

		void SetSize(float _w, float _h)
		{
			size = Vector2(_w, _h);
		}
	};
}