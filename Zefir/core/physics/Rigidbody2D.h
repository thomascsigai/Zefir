#pragma once

#include <Vector2.h>

namespace Zefir
{
	enum BodyType
	{
		Static,
		Kinematic,
		Dynamic
	};

	struct Rigidbody2D
	{
		BodyType type = BodyType::Dynamic;
		Vector2 velocity = { 0, 0 };
		float mass = 1.0f;
		bool useGravity = true;
	};
}