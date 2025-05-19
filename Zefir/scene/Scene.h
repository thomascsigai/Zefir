#pragma once

#include <core/EngineContext.h>

namespace Zefir
{
	class Scene
	{
	protected:
		EngineContext* m_EngineContext;

	public:
		virtual ~Scene() = default;
		virtual void OnLoad() {}
		virtual void OnUnload() {}
		virtual void Update(double deltaTime) = 0;
		virtual void Render(const std::unique_ptr<Renderer>& renderer) = 0;
		virtual void OnEvent(const SDL_Event& e) {}

		virtual void OnAttach(EngineContext* context) { m_EngineContext = context; }
	};
}