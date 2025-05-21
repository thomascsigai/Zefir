#include <core/debug/ImGuiManager.h>

namespace Zefir
{
	ImGuiManager::ImGuiManager(Window* window, Renderer* renderer)
	{
		if (!Init(window, renderer))
		{
			LOG_WARN("ImGui could not be initialized.");
		}
	}

	ImGuiManager::~ImGuiManager()
	{
		Shutdown();
	}

	void ImGuiManager::HandleEvent(const SDL_Event& e)
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	void ImGuiManager::NewWindow()
	{
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		if (ImGui::Begin("Performance"))
		{
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
			ImGui::Text("Delta Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
		}
		ImGui::End();
	}

	void ImGuiManager::Render(Renderer* renderer)
	{
		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer->GetSDLRenderer());
	}

	bool ImGuiManager::Init(Window* window, Renderer* renderer)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg].w = 0.5f;

		if (!ImGui_ImplSDL2_InitForSDLRenderer(window->GetSDLWindow(), renderer->GetSDLRenderer())
			|| !ImGui_ImplSDLRenderer2_Init(renderer->GetSDLRenderer()))
		{
			return false;
		}

		return true;
	}

	void ImGuiManager::Shutdown()
	{
		ImGui_ImplSDLRenderer2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}
}