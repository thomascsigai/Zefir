#pragma once

#include <SDL.h>

#include <core/window/Window.h>
#include <renderer/Renderer.h>
#include <sound/SoundManager.h>
#include <resource/ResourceManager.h>

namespace Zefir
{
	class Application
	{
	protected:
		Window m_Window;
		Renderer m_Renderer;
		ResourceManager m_ResourceManager;
		SoundManager m_SoundManager;

	public:
		Application()
			: m_IsRunning(true), m_Window(), m_Renderer(&m_Window),
			m_ResourceManager(&m_Renderer), m_SoundManager()
		{
		}

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(SDL_Event& e) = 0;
		virtual void Render() = 0;
		virtual void Exit() = 0;

		bool IsRunning() 
		{
			return m_IsRunning;
		}

		void SetIsRunning(const bool& b)
		{
			m_IsRunning = b;
		}

		SDL_Renderer* GetSDLRenderer()
		{
			return m_Renderer.GetSDLRenderer();
		}

		double m_DeltaTime;

	private:
		bool m_IsRunning;
	};
}