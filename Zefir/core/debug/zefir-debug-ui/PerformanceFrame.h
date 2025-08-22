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
			static int fpsIndex = 0;

			static float fpsHistory[100] = { 0.0f };
			static float updateHistory[100] = { 0.0f };
			static float renderHistory[100] = { 0.0f };
			static float physicsHistory[100] = { 0.0f };
			static float eventHistory[100] = { 0.0f };
						
			fpsHistory[fpsIndex] = ImGui::GetIO().Framerate;
			updateHistory[fpsIndex] = m_ProfilingData.updateTime;
			renderHistory[fpsIndex] = m_ProfilingData.renderTime;
			physicsHistory[fpsIndex] = m_ProfilingData.physicsTime;
			eventHistory[fpsIndex] = m_ProfilingData.eventHandlingTime;

			fpsIndex = (fpsIndex + 1) % IM_ARRAYSIZE(fpsHistory);

			float avg = 0.0f;
			for (float f : fpsHistory) avg += f;
			avg /= IM_ARRAYSIZE(fpsHistory);

			ImGui::Text("FPS: %.1f", fpsHistory[(fpsIndex - 1 + IM_ARRAYSIZE(fpsHistory)) % IM_ARRAYSIZE(fpsHistory)]);
			ImGui::PlotLines("FPS", fpsHistory, IM_ARRAYSIZE(fpsHistory), fpsIndex,
				"FPS", 0.0f, 144.0f, ImVec2(0, 80));
			ImGui::Text("Delta Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
			
			ImGui::Text("Update time: %.3f  ms", m_ProfilingData.updateTime);
			ImGui::PlotLines("Update (ms)", updateHistory, IM_ARRAYSIZE(updateHistory), fpsIndex,
				NULL, 0.0f, 10.0f, ImVec2(0, 60));

			ImGui::Text("Render time: %.3f ms", m_ProfilingData.renderTime);
			ImGui::PlotLines("Render (ms)", renderHistory, IM_ARRAYSIZE(renderHistory), fpsIndex,
				NULL, 0.0f, 40.0f, ImVec2(0, 60));

			ImGui::Text("Physics time: %.3f  ms", m_ProfilingData.physicsTime);
			ImGui::PlotLines("Physics (ms)", physicsHistory, IM_ARRAYSIZE(physicsHistory), fpsIndex,
				NULL, 0.0f, 10.0f, ImVec2(0, 60));

			ImGui::Text("Evnts Handling time: %.3f  ms", m_ProfilingData.eventHandlingTime);
			ImGui::PlotLines("Events (ms)", eventHistory, IM_ARRAYSIZE(eventHistory), fpsIndex,
				NULL, 0.0f, 10.0f, ImVec2(0, 60));
		}

		void UpdateProfilingData(const ProfilingData& data)
		{
			m_ProfilingData = data;
		}

	private:
		ProfilingData m_ProfilingData;
	};
}