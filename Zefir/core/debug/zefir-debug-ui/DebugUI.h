#pragma once

#include <core/debug/ImGuiManager.h>

#include <core/debug/zefir-debug-ui/PerformanceFrame.h>
#include <core/debug/zefir-debug-ui/LogFrame.h>
#include <core/debug/zefir-debug-ui/SimulationControlFrame.h>
#include <core/debug/zefir-debug-ui/ResourcesFrame.h>
#include <core/debug/zefir-debug-ui/CameraFrame.h>

namespace Zefir
{
	class DebugUI
	{
	public:
		DebugUI()
		{
			m_PerformanceFrame = std::make_unique<PerformanceFrame>();
			m_LogFrame = std::make_unique<LogFrame>();
			m_SimulationControlFrame = std::make_unique<SimulationControlFrame>();
			m_ResourcesFrame = std::make_unique<ResourcesFrame>();
			m_CameraFrame = std::make_unique<CameraFrame>();
		}

		void HandleEvent(SDL_Event& e)
		{
			if (e.type == APP_LOG)
			{
				HandleAppLogEvent(e);
			}
			
			if (e.type == EngineEvents::UPDATE_PROFILING_DATA)
			{
				if (m_PerformanceFrame)
				{
					ProfilingData* newData = static_cast<ProfilingData*>(e.user.data1);
					m_PerformanceFrame->UpdateProfilingData(*newData);
					delete(newData);
				}
			}
		}

		void ShowUI(ImGuiManager* imGuiManager)
		{
			if (imGuiManager == nullptr)
			{
				LOG_WARN("Debug UI could not be drawn. ImGuiManager does not exist or is not initialized.");
				return;
			}

			//ImGui::ShowDemoWindow();
			if (m_PerformanceFrame) imGuiManager->NewFrame(m_PerformanceFrame.get());
			if (m_LogFrame) imGuiManager->NewFrame(m_LogFrame.get());
			if (m_SimulationControlFrame) imGuiManager->NewFrame(m_SimulationControlFrame.get());
			if (m_ResourcesFrame) imGuiManager->NewFrame(m_ResourcesFrame.get());
			if (m_CameraFrame) imGuiManager->NewFrame(m_CameraFrame.get());
		}


		void Clear()
		{
			ImDrawData* data = ImGui::GetDrawData();
			if (data) data->Clear();
		}

	private:
		ImGuiManager* m_ImguiManager = nullptr;

		std::unique_ptr<PerformanceFrame> m_PerformanceFrame;
		std::unique_ptr<LogFrame> m_LogFrame;
		std::unique_ptr<SimulationControlFrame> m_SimulationControlFrame;
		std::unique_ptr<ResourcesFrame> m_ResourcesFrame;
		std::unique_ptr<CameraFrame> m_CameraFrame;
		
		void AddLogToLogPanel(const std::string& msg)
		{
			if (m_LogFrame)
			{
				m_LogFrame->AddLog(msg.c_str());
			}
		}

		void HandleAppLogEvent(SDL_Event& e)
		{
			std::string* msg = static_cast<std::string*>(e.user.data1);
			int* severity = static_cast<int*>(e.user.data2);

			if (msg && severity)
			{
				if (*severity == 0) AddLogToLogPanel("[INFO] " + *msg + "\n");
				if (*severity == 1) AddLogToLogPanel("[WARN] " + *msg + "\n");
				if (*severity == 2) AddLogToLogPanel("[FATAL] " + *msg + "\n");
			}

			delete msg;
			delete severity;
		}
	};
}