#pragma once 

#include <iostream>

namespace Djipi
{
	struct Vector2
	{
		float x, y;

		Vector2() = default;

		Vector2(float _x, float _y)
			: x(_x), y(_y) {
		}

		// Operators overloads ------------------

		// Access components by index
		float& operator [](int i);
		const float& operator [](int i) const;

		// Scalar multiplication
		Vector2& operator /=(float s);
		Vector2& operator *=(float s);

		// Addition & substraction
		Vector2& operator +=(const Vector2& v);
		Vector2& operator -=(const Vector2& v);
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

	inline Vector2 operator+(const Vector2& v1, const Vector2& v2)
	{
		return (Vector2(v1.x + v2.x, v1.y + v2.y));
	}
	
	inline Vector2 operator-(const Vector2& v1, const Vector2& v2)
	{
		return (Vector2(v1.x - v2.x, v1.y - v2.y));
	}

	inline float Dot(const Vector2& v1, const Vector2& v2)
	{
		return (v1.x * v2.x + v1.y * v2.y);
	}

	inline Vector2 Project(const Vector2& v1, const Vector2 v2)
	{
		return (v2 * (Dot(v1, v2) / Dot(v2, v2)));
	}

	inline Vector2 Reject(const Vector2& v1, const Vector2& v2)
	{
		return (v1 - v2 * (Dot(v1, v2) / Dot(v2, v2)));
	}

	
	// << operator overload to cout vector components
	std::ostream& operator<<(std::ostream& os, const Vector2& v);
}