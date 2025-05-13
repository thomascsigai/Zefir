#pragma once

#include <core/math/Vector2.h>

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
		Vector2 acceleration = { 0, 0 };
		float mass = 1.0f;
		bool useGravity = true;

		void AddForce(const Vector2& force)
		{
			acceleration += force / mass;
		}

		void Integrate(double deltaTime)
		{
			velocity += acceleration * deltaTime;
			acceleration = { 0, 0 };
		}
	};
}