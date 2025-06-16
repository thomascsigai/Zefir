#pragma once

#include <SDL.h>

#include <core/window/Window.h>
#include <core/EngineContext.h>
#include <core/EngineEvents.h>
#include <renderer/Renderer.h>
#include <sound/SoundManager.h>
#include <resource/ResourceManager.h>
#include <scene/SceneManager.h>

#include <core/debug/ImGuiManager.h>
#include <core/debug/zefir-debug-ui/DebugUI.h>

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
		std::unique_ptr<ImGuiManager> m_ImGuiManager;

		EngineContext m_EngineContext;

#ifndef NDEBUG
		std::unique_ptr<DebugUI> m_DebugUI;
		bool m_HideDebugUI;
#endif

	public:
		Application();

		bool Init();
		virtual void OnInit() = 0;
		
		void Update();
		
		void OnEvent(SDL_Event& e);
		virtual void HandleEvents(SDL_Event& e) = 0;
		
		void Render();
		void Exit();

		bool IsRunning();

	private:
		bool m_IsRunning;
		bool m_IsPaused;
		bool m_SpeedUp;

		double m_DeltaTime;
		int m_PreviousTime;
		int m_CurrentTime;
	};
}