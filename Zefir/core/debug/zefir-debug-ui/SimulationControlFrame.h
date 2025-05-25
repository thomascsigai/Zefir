#pragma once

#include <core/debug/ImGuiManager.h>

namespace Zefir
{
	struct SimulationControlFrame : public ImGuiFrame
	{
        std::string GetName() override
		{
			return ("Simulation Control");
		}

		void ShowContent() override
		{
			if (ImGui::Button("Pause"))
			{
				m_PausePressed = !m_PausePressed;
				SDL_Event e = { EngineEvents::PAUSE_SIMULATION };
				SDL_PushEvent(&e);
			};ImGui::SameLine();

			if (ImGui::Button("Resume"))
			{
				SDL_Event e = { EngineEvents::RESUME_SIMULATION };
				SDL_PushEvent(&e);
			};ImGui::SameLine();

			if(ImGui::Button("Speed x2"))
			{
				SDL_Event e = { EngineEvents::SPEED_UP_SIMULATION };
				SDL_PushEvent(&e);
			}
		}

	private:
		bool m_PausePressed = false;
	};
}