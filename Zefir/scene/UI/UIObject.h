#pragma once

#include <core/math/Vector2.h>
#include <renderer/Renderer.h>

namespace Zefir
{
	class UIObject
	{
	public:
		UIObject(float x, float y, float w, float h)
			: m_Position(x, y), m_Size(w, h) {}

		int m_Id;
		Vector2 m_Position;
		Vector2 m_Size;

		virtual void Update() = 0;
		virtual void Render(Renderer* renderer, const Camera& cam) = 0;
	};
}