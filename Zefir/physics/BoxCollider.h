#pragma once

#include <core/math/Vector2.h>

namespace Zefir
{
	struct BoxCollider
	{
		Vector2 position = { 0, 0 };
		Vector2 size = { 0, 0 };
	};
}