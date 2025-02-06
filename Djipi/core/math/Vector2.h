#pragma once 

#include <iostream>

namespace Djipi
{
	struct Vector2
	{
		float x, y;

		Vector2() = default;

		Vector2(float _x, float _y)
			: x(_x), y(_y) {}

		// Operators overloads ------------------

		// Access components by index
		float& operator [](int i);
		const float& operator [](int i) const;

		// Scalar multiplication
		Vector2& operator /=(float s);
		Vector2& operator *=(float s);
	};
	
	// << operator overload to cout vector components
	std::ostream& operator<<(std::ostream& os, const Vector2& v);
}