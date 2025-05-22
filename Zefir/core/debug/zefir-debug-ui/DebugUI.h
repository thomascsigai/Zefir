#pragma once

#include <core/debug/ImGuiManager.h>

#include <core/debug/zefir-debug-ui/PerformanceFrame.h>
#include <core/debug/zefir-debug-ui/LogFrame.h>

namespace Zefir
{
	class DebugUI
	{
	public:
		DebugUI()
		{
			performanceFrame = std::make_unique<PerformanceFrame>();
			logFrame = std::make_unique<LogFrame>();
		}

		void ShowUI(ImGuiManager* imGuiManager)
		{
			if (imGuiManager == nullptr)
			{
				LOG_WARN("Debug UI could not be drawn. ImGuiManager does not exist or is not initialized.");
				return;
			}

			ImGui::ShowDemoWindow();
			if (performanceFrame) imGuiManager->NewFrame(performanceFrame.get());
			if (logFrame) imGuiManager->NewFrame(logFrame.get());
		}

		void AddLogToLogPanel()
		{
			if (logFrame) logFrame->AddLog("Test");
		}

		void Clear()
		{
			ImDrawData* data = ImGui::GetDrawData();
			if (data) data->Clear();
		}

	private:
		ImGuiManager* m_ImguiManager = nullptr;

		std::unique_ptr<PerformanceFrame> performanceFrame;
		std::unique_ptr<LogFrame> logFrame;
	};
}