#pragma once

#include <core/debug/zefir-debug-ui/PerformanceFrame.h>
#include <core/debug/ImGuiManager.h>

namespace Zefir
{
	class DebugUI
	{
	public:
		DebugUI()
		{
			performanceFrame = std::make_unique<PerformanceFrame>();
		}

		void ShowUI(ImGuiManager* imGuiManager)
		{
			if (imGuiManager == nullptr)
			{
				LOG_WARN("Debug UI could not be drawn. ImGuiManager does not exist or is not initialized.");
				return;
			}

			if (performanceFrame) imGuiManager->NewFrame(performanceFrame.get());
		}

		void Clear()
		{
			ImDrawData* data = ImGui::GetDrawData();
			if (data) data->Clear();
		}

	private:
		ImGuiManager* m_ImguiManager = nullptr;
		std::unique_ptr<PerformanceFrame> performanceFrame;
	};
}