#pragma once

#include <core/math/Vector2.h>

namespace Zefir
{
	struct Camera
	{
		Vector2 position = { 0, 0 };
		double zoom = 0;
	};
}