#pragma once

#include <SDL.h>
#include <core/math/Vector2.h>

namespace Zefir
{
	struct Transform2D
	{
		Vector2 position = Vector2(0, 0);
		Vector2 oldPosition = Vector2(0, 0); // Used to render interpolated position
		Vector2 size = Vector2(0, 0); // In Meters
		double rotation = 0; // In Radians


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

		void SetRotation(double r)
		{
			rotation = r;
		}
	};
}