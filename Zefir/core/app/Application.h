#pragma once

#include <SDL.h>

#include <core/window/Window.h>
#include <core/EngineContext.h>
#include <renderer/Renderer.h>
#include <sound/SoundManager.h>
#include <resource/ResourceManager.h>
#include <scene/SceneManager.h>

namespace Zefir
{
	class Application
	{
	protected:
		// Application systems
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<ResourceManager> m_ResourceManager;
		std::unique_ptr<SoundManager> m_SoundManager;
		std::unique_ptr<SceneManager> m_SceneManager;

		EngineContext m_EngineContext;

	public:
		Application();

		bool Init();
		virtual void OnInit() = 0;
		
		void Update();
		
		void OnEvent(SDL_Event& e);
		virtual void CustomEvents(SDL_Event& e) = 0;
		
		void Render();
		void Exit();

		bool IsRunning();
		double m_DeltaTime;

	private:
		bool m_IsRunning;
	};
}