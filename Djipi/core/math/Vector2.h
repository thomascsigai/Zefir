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

	// Vector2 operations functions
	inline Vector2 operator *(const Vector2& v, float s)
	{
		return (Vector2(v.x * s, v.y * s));
	}

	inline Vector2 operator /(const Vector2& v, float s)
	{
		s = 1.0f / s;
		return (Vector2(v.x * s, v.y * s));
	}

	inline Vector2 operator -(const Vector2& v)
	{
		return (Vector2(-v.x, -v.y));
	}

	inline float Magnitude(const Vector2& v)
	{
		return (sqrt(v.x * v.x + v.y * v.y));
	}

	inline Vector2 Normalize(const Vector2& v)
	{
		return (v / Magnitude(v));
	}

	
	// << operator overload to cout vector components
	std::ostream& operator<<(std::ostream& os, const Vector2& v);
}