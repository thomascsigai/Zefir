#pragma once

namespace Zefir
{
	class Scene
	{
	public:
		virtual ~Scene() = default;
		virtual void OnLoad() {}
		virtual void OnUnload() {}
		virtual void Update(double deltaTime) = 0;
		virtual void Render() = 0;
		virtual void OnEvent(const SDL_Event& e) {}
	};
}