#include <core/app/Application.h>

namespace Zefir
{
	Application::Application() : m_IsRunning(false)
	{
		m_DeltaTime = 0;
	}

	bool Application::Init()
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

		// Setup EngineContext
		m_EngineContext.window = m_Window.get();
		m_EngineContext.renderer = m_Renderer.get();
		m_EngineContext.resourceManager = m_ResourceManager.get();
		m_EngineContext.soundManager = m_SoundManager.get();

		OnInit();

		m_IsRunning = true;
		return true;
	}

	void Application::Update()
	{
		m_SceneManager->Update(m_DeltaTime);
	}

	void Application::OnEvent(SDL_Event& e)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				m_IsRunning = false;
			}

			m_SceneManager->OnEvent(e);
			HandleEvents(e);
		}
	}

	void Application::Render()
	{
		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer->GetSDLRenderer());
		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 255, 255, 255, 255);

		m_SceneManager->Render(m_Renderer);

		SDL_RenderPresent(m_Renderer->GetSDLRenderer());
	}

	void Application::Exit()
	{
		SDL_Quit();
	}

	bool Application::IsRunning()
	{
		return m_IsRunning;
	}
}