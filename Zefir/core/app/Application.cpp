#include <core/app/Application.h>
#include <core/debug/zefir-debug-ui/PerformanceFrame.h>

namespace Zefir
{
	Application::Application() : m_IsRunning(false), m_IsPaused(false)
	{
		m_DeltaTime = 0;
		m_CurrentTime = 0;
		m_PreviousTime = SDL_GetTicks();
	}

	bool Application::Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			LOG_FATAL("SDL could not initialize ! SDL_Error: ", SDL_GetError());
			return false;
		}

		// Systems instanciation & initialization
		m_Window = std::make_unique<Window>();
		m_Renderer = std::make_unique<Renderer>(m_Window.get());
		m_SoundManager = std::make_unique<SoundManager>();
		m_ResourceManager = std::make_unique<ResourceManager>(m_Renderer.get());
		m_SceneManager = std::make_unique<SceneManager>();
		m_ImGuiManager = std::make_unique<ImGuiManager>(m_Window.get(), m_Renderer.get());

		// Setup EngineContext
		m_EngineContext.window = m_Window.get();
		m_EngineContext.renderer = m_Renderer.get();
		m_EngineContext.resourceManager = m_ResourceManager.get();
		m_EngineContext.soundManager = m_SoundManager.get();
		m_EngineContext.imGuiManager = m_ImGuiManager.get();

#ifndef NDEBUG
		m_DebugUI = std::make_unique<DebugUI>();
		m_HideDebugUI = true;
#endif

		OnInit();

		m_IsRunning = true;
		return true;
	}

	void Application::Update()
	{
		if (!m_IsPaused)
		{
			m_CurrentTime = SDL_GetTicks();
			m_DeltaTime = (double)(m_CurrentTime - m_PreviousTime) / 1000;
			m_PreviousTime = m_CurrentTime;

			m_SceneManager->Update(m_DeltaTime);
		}

		// UI
		m_ImGuiManager->Update();

#ifndef NDEBUG
		if (!m_HideDebugUI && m_DebugUI != nullptr)
		{
			m_DebugUI->ShowUI(m_ImGuiManager.get());
		}
		else
		{
			m_DebugUI->Clear();
		}
#endif
	}

	void Application::OnEvent(SDL_Event& e)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				m_IsRunning = false;
			}

			if (e.type == EngineEvents::PAUSE_SIMULATION)
			{
				m_IsPaused = true;
			}

			if (e.type == EngineEvents::RESUME_SIMULATION)
			{
				m_IsPaused = false;
			}

			m_SceneManager->OnEvent(e);
			HandleEvents(e);

			m_ImGuiManager->HandleEvent(e);

#ifndef NDEBUG
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{

				if (e.key.keysym.sym == SDLK_F1)
				{
					m_HideDebugUI = !m_HideDebugUI;
				}
			}

			m_DebugUI->HandleEvent(e);
#endif
		}

	}

	void Application::Render()
	{
		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer->GetSDLRenderer());
		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 255, 255, 255, 255);

		m_SceneManager->Render(m_Renderer);
		m_ImGuiManager->Render(m_Renderer.get());

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