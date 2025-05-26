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
				m_PausePressed = true;
				m_SpeedUpPressed = false;
				SDL_Event e = { EngineEvents::PAUSE_SIMULATION };
				SDL_PushEvent(&e);
			} ImGui::SameLine();

			if (ImGui::Button("Resume"))
			{
				m_PausePressed = false;
				m_SpeedUpPressed = false;
				SDL_Event e = { EngineEvents::RESUME_SIMULATION };
				SDL_PushEvent(&e);
			} ImGui::SameLine();

			if(ImGui::Button("Speed x2"))
			{
				m_PausePressed = false;
				m_SpeedUpPressed = true;
				SDL_Event e = { EngineEvents::SPEED_UP_SIMULATION };
				SDL_PushEvent(&e);
			} ImGui::SameLine();

			if (m_PausePressed) ImGui::Text("(Paused)");
			if (m_SpeedUpPressed) ImGui::Text("(Speed x2)");
		}

	private:
		bool m_PausePressed = false;
		bool m_SpeedUpPressed = false;
	};
}