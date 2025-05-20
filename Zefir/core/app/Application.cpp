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
		m_SoundManager = std::make_unique<SoundManager>();
		m_ResourceManager = std::make_unique<ResourceManager>(m_Renderer.get());
		m_SceneManager = std::make_unique<SceneManager>();

		// Setup EngineContext
		m_EngineContext.window = m_Window.get();
		m_EngineContext.renderer = m_Renderer.get();
		m_EngineContext.resourceManager = m_ResourceManager.get();
		m_EngineContext.soundManager = m_SoundManager.get();

		// Setup Dear ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForSDLRenderer(m_Window->GetSDLWindow(), m_Renderer->GetSDLRenderer());
		ImGui_ImplSDLRenderer2_Init(m_Renderer->GetSDLRenderer());

		OnInit();

		m_IsRunning = true;
		return true;
	}

	void Application::Update()
	{
		m_SceneManager->Update(m_DeltaTime);

		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow();
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
			ImGui_ImplSDL2_ProcessEvent(&e);
		}

	}

	void Application::Render()
	{
		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer->GetSDLRenderer());
		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 255, 255, 255, 255);

		m_SceneManager->Render(m_Renderer);

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_Renderer->GetSDLRenderer());

		SDL_RenderPresent(m_Renderer->GetSDLRenderer());
	}

	void Application::Exit()
	{
		ImGui_ImplSDLRenderer2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		SDL_Quit();
	}

	bool Application::IsRunning()
	{
		return m_IsRunning;
	}
}