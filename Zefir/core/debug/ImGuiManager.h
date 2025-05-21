#pragma once

#include <core/debug/Log.h>
#include <renderer/Renderer.h>                                                                       

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

namespace Zefir
{
	struct ImGuiFrame
	{
		virtual std::string GetName() const = 0;
		virtual void ShowContent() const = 0;
	};

	class ImGuiManager
	{
	public:
		ImGuiManager(Window* window, Renderer* renderer);

		~ImGuiManager();

		void HandleEvent(const SDL_Event& e);
		void Render(Renderer* renderer);

		void NewFrame(ImGuiFrame* frame);

	private:
		bool Init(Window* window, Renderer* renderer);
		void Shutdown();

	};
}