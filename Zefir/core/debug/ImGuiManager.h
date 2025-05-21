#pragma once

#include <core/debug/Log.h>
#include <renderer/Renderer.h>                                                                       

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

namespace Zefir
{
	struct ImGuiWindow
	{
		std::string m_Name;

		ImGuiWindow(std::string name) : m_Name(name) {}
		virtual void GetContent() = 0;
	};

	class ImGuiManager
	{
	public:
		ImGuiManager(Window* window, Renderer* renderer);

		~ImGuiManager();

		void HandleEvent(const SDL_Event& e);
		void Render(Renderer* renderer);

		void NewWindow();

	private:
		bool Init(Window* window, Renderer* renderer);
		void Shutdown();

	};
}