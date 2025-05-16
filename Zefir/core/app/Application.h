#pragma once

#include <SDL.h>

#include <core/window/Window.h>
#include <renderer/Renderer.h>
#include <sound/SoundManager.h>
#include <resource/ResourceManager.h>
#include <scene/SceneManager.h>

namespace Zefir
{
	class Application
	{
	private:
		// Application systems
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<ResourceManager> m_ResourceManager;
		std::unique_ptr<SoundManager> m_SoundManager;
		std::unique_ptr<SceneManager> m_SceneManager;

	public:
		Application() : m_IsRunning(false)
		{}

		bool Init()
		{
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
			{
				LOG_FATAL("SDL could not initialize ! SDL_Error: " << SDL_GetError());
				return false;
			}

			// Systems instanciation & initialization
			m_Window = std::make_unique<Window>();
			m_Renderer = std::make_unique<Renderer>(m_Window.get());
			m_ResourceManager = std::make_unique<ResourceManager>(m_Renderer.get());
			m_SoundManager = std::make_unique<SoundManager>();
			m_SceneManager = std::make_unique<SceneManager>();

			m_IsRunning = true;
			return true;
		}

		void Update()
		{
			m_SceneManager->Update(m_DeltaTime);
		}

		void OnEvent(SDL_Event& e)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					m_IsRunning = false;
				}

				m_SceneManager->OnEvent(e);
			}
		}

		void Render()
		{
			SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 0, 0, 0, 255);
			SDL_RenderClear(m_Renderer->GetSDLRenderer());
			SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 255, 255, 255, 255);

			m_SceneManager->Render();

			SDL_RenderPresent(m_Renderer->GetSDLRenderer());
		}

		void Exit()
		{
			SDL_Quit();
		}

		bool IsRunning() 
		{
			return m_IsRunning;
		}

		SDL_Renderer* GetSDLRenderer()
		{
			return m_Renderer->GetSDLRenderer();
		}

		double m_DeltaTime;

	private:
		bool m_IsRunning;
	};
}