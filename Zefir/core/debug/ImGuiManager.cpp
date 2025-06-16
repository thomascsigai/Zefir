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

	void ImGuiManager::NewFrame(ImGuiFrame* frame)
	{
		ImGui::Begin(frame->GetName().c_str());
		frame->ShowContent();
		ImGui::End();
	}

	void ImGuiManager::Render(Renderer* renderer)
	{
		ImGui::Render();
		ImDrawData* drawData = ImGui::GetDrawData();
		if (drawData && drawData->Valid)
		{
			ImGui_ImplSDLRenderer2_RenderDrawData(drawData, renderer->GetSDLRenderer());
		}
	}

	void ImGuiManager::Update()
	{
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
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