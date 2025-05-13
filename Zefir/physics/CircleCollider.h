#pragma once

#include <core/math/Vector2.h>

namespace Zefir
{
	struct CircleCollider
	{
		float radius = 1;
		Vector2 position = { 0, 0 };
	};
}