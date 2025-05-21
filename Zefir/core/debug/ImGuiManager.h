#pragma once

#include <core/debug/Log.h>
#include <renderer/Renderer.h>                                                                       

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

namespace Zefir
{
	class ImGuiManager
	{
	public:
		ImGuiManager(Window* window, Renderer* renderer)
		{
			if (!Init(window, renderer))
			{
				LOG_WARN("ImGui could not be initialized.");
			}
		}

		~ImGuiManager()
		{
			Shutdown();
		}

		void HandleEvent(const SDL_Event& e)
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
		}

		void NewWindow()
		{
			ImGui_ImplSDLRenderer2_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();
			
			ImGui::Begin("Test");

			ImGui::End();

			ImGui::ShowDemoWindow();
		}

		void Render(Renderer* renderer)
		{
			ImGui::Render();
			ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer->GetSDLRenderer());
		}

	private:
		bool Init(Window* window, Renderer* renderer)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

			ImGui::StyleColorsDark();
			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				ImGuiStyle& style = ImGui::GetStyle();
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 0.5f;
			}

			if (!ImGui_ImplSDL2_InitForSDLRenderer(window->GetSDLWindow(), renderer->GetSDLRenderer())
				|| !ImGui_ImplSDLRenderer2_Init(renderer->GetSDLRenderer()))
			{
				return false;
			}

			return true;
		}

		void Shutdown()
		{
			ImGui_ImplSDLRenderer2_Shutdown();
			ImGui_ImplSDL2_Shutdown();
			ImGui::DestroyContext();
		}

	};
}