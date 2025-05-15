#pragma once

#include <SDL.h>

namespace Zefir
{
	class Application
	{
	public:
		Application()
			: m_IsRunning(true)
		{
		}

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(SDL_Event& e) = 0;
		virtual void Exit() = 0;

		bool IsRunning() 
		{
			return m_IsRunning;
		}

	private:
		bool m_IsRunning;
	};
}