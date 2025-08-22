#include <core/app/Application.h>
#include <core/debug/zefir-debug-ui/PerformanceFrame.h>

namespace Zefir
{
	Application::Application() : m_IsRunning(false), m_IsPaused(false), m_SpeedUp(false)
	{
		m_DeltaTime = 0;
		m_CurrentTime = 0;
		m_PreviousTime = SDL_GetTicks();

#ifndef NDEBUG
		m_ProfilingData = ProfilingData();
#endif 

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
		m_CurrentTime = SDL_GetTicks();
		m_DeltaTime = (double)(m_CurrentTime - m_PreviousTime) / 1000;
		m_PreviousTime = m_CurrentTime;
		
		if (!m_IsPaused)
		{
			m_SceneManager->Update(m_DeltaTime);
			if (m_SpeedUp) m_SceneManager->Update(m_DeltaTime);
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
				m_SpeedUp = false;
			}

			if (e.type == EngineEvents::RESUME_SIMULATION)
			{
				m_IsPaused = false;
				m_SpeedUp = false;
			}

			if (e.type == EngineEvents::SPEED_UP_SIMULATION)
			{
				m_IsPaused = false;
				m_SpeedUp = true;
			}

			if (e.type == EngineEvents::LOAD_ALL_RESOURCES)
			{
				m_ResourceManager->LoadAllResources();
			}

			if (e.type == EngineEvents::RELOAD_ALL_RESOURCES)
			{
				m_ResourceManager->ReloadAllResources();
			}

			if (e.type == EngineEvents::UNLOAD_ALL_RESOURCES)
			{
				m_ResourceManager->UnloadAllResources();
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
#ifndef NDEBUG
		Uint64 start = SDL_GetPerformanceCounter();
#endif

		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer->GetSDLRenderer());
		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 255, 255, 255, 255);

		m_SceneManager->Render(m_Renderer.get());
		m_ImGuiManager->Render(m_Renderer.get());

		SDL_RenderPresent(m_Renderer->GetSDLRenderer());

#ifndef NDEBUG
		Uint64 end = SDL_GetPerformanceCounter();
		double elapsedMSeconds = (double)(end - start) / (double)SDL_GetPerformanceFrequency() * 1000;
		m_ProfilingData.renderTime = elapsedMSeconds;
#endif
	}

	void Application::Exit()
	{
		SDL_Quit();
	}

	bool Application::IsRunning()
	{
		return m_IsRunning;
	}

#ifndef NDEBUG
	void Application::SendProfilingData()
	{
		SDL_Event e = { EngineEvents::UPDATE_PROFILING_DATA };
		ProfilingData* data = new ProfilingData();
		data->renderTime = m_ProfilingData.renderTime;
		e.user.data1 = data;
		SDL_PushEvent(&e);
	}
#endif

}