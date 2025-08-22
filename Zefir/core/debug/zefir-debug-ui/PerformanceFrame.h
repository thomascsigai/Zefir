#pragma once

#include <core/debug/ImGuiManager.h>
#include <core/debug/ProfilingData.h>

namespace Zefir
{
	struct PerformanceFrame : public ImGuiFrame
	{
		PerformanceFrame() : m_ProfilingData()
		{ }

		std::string GetName() override
		{
			return ("Performance");
		}

		void ShowContent() override
		{
			static float fpsHistory[100] = { 0.0f };
			static int fpsIndex = 0;
						
			fpsHistory[fpsIndex] = ImGui::GetIO().Framerate;
			fpsIndex = (fpsIndex + 1) % IM_ARRAYSIZE(fpsHistory);

			float avg = 0.0f;
			for (float f : fpsHistory) avg += f;
			avg /= IM_ARRAYSIZE(fpsHistory);

			ImGui::Text("FPS: %.1f", fpsHistory[(fpsIndex - 1 + IM_ARRAYSIZE(fpsHistory)) % IM_ARRAYSIZE(fpsHistory)]);
			ImGui::PlotLines("FPS", fpsHistory, IM_ARRAYSIZE(fpsHistory), fpsIndex,
				"FPS", 0.0f, 144.0f, ImVec2(0, 80));
			ImGui::Text("Delta Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
			ImGui::Text("Evnts Handling time: 0 ms");
			ImGui::Text("Update time: 0 ms");
			ImGui::Text("Render time: %.3f ms", m_ProfilingData.renderTime);
			ImGui::Text("Physics time: 0 ms");
		}

		void UpdateProfilingData(const ProfilingData& data)
		{
			m_ProfilingData = data;
		}

	private:
		ProfilingData m_ProfilingData;
	};
}