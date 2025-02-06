#pragma once 

struct Vector2
{
	float x, y;

	Vector2() = default;

	Vector2(float _x, float _y)
		: x(_x), y(_y) { }

	float& operator [](int i)
	{
		return ((&x)[i]);
	}
	
	const float& operator [](int i) const
	{
		return ((&x)[i]);
	}
};