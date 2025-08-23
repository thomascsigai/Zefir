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
            static bool profilingPaused = false;

			static int fpsIndex = 0;

			static float fpsHistory[100] = { 0.0f };
            static float avgHistory[100] = { 0.0f };
			
            static float avg = 0.0f;
            static float fps = 0.0f;
            static float frameTimeMs = 0.0f;
            static float deltaTime = 0.0f;
			
            if (!profilingPaused)
            {
			    fpsHistory[fpsIndex] = 1000 / m_ProfilingData.frameTime;

			    fpsIndex = (fpsIndex + 1) % IM_ARRAYSIZE(fpsHistory);
			    
                for (float f : fpsHistory) avg += f;
			    avg /= IM_ARRAYSIZE(fpsHistory);
                avgHistory[fpsIndex] = avg;

                fps = fpsHistory[(fpsIndex - 1 + IM_ARRAYSIZE(fpsHistory)) % IM_ARRAYSIZE(fpsHistory)];
                frameTimeMs = m_ProfilingData.frameTime;
                deltaTime = m_ProfilingData.deltaTime;
            }

            if (profilingPaused)
            {
                if (ImGui::Button("Resume Profiling"))
                    profilingPaused = false;
            }
            else
            {
                if (ImGui::Button("Pause Profiling"))
                    profilingPaused = true;
            }

            ImGui::Separator();

            ImGui::Text("Average FPS: %.1f", avg);
            ImGui::PlotLines("##avgfps", avgHistory, IM_ARRAYSIZE(avgHistory), 0, nullptr, 0.0f, 240.0f, ImVec2(-1, 80));
            ImGui::Text("Frame Time: %.3f ms", frameTimeMs);
            ImGui::Text("Delta Time: %.3f s", deltaTime);

            ImGui::Separator();

            if (ImGui::CollapsingHeader("Frame Stats"))
            {
                static float minFrame = FLT_MAX, maxFrame = 0.0f, avgFrame = 0.0f;
                static float updateMs = 0.0f, renderMs = 0.0f, eventsMs = 0.0f, totalMs = 0.0f;
                
                if (!profilingPaused)
                {
                    for (int i = 0; i < IM_ARRAYSIZE(fpsHistory); i++)
                    {
                        float ft = m_ProfilingData.frameTime;
                        minFrame = (ft < minFrame) ? ft : minFrame;
                        maxFrame = (ft > maxFrame) ? ft : maxFrame;
                        avgFrame += ft;
                    }
                    avgFrame /= IM_ARRAYSIZE(fpsHistory);
                    
                    updateMs = m_ProfilingData.updateTime;
                    renderMs = m_ProfilingData.renderTime;
                    eventsMs = m_ProfilingData.eventHandlingTime;
                    totalMs = updateMs + renderMs + eventsMs;
                }            

                // Affichage résumé
                ImGui::Text("Frame Time: Avg %.2f ms | Min %.2f ms | Max %.2f ms",
                    avgFrame, minFrame, maxFrame);

                // Affichage temps par sous-système
                ImGui::Text("(0) Update: %.3f ms (%.0f%%)", updateMs, (updateMs / totalMs) * 100.0f);
                ImGui::Text("(1) Render: %.3f ms (%.0f%%)", renderMs, (renderMs / totalMs) * 100.0f);
                ImGui::Text("(2) Events Handling: %.3f ms (%.0f%%)", eventsMs, (eventsMs / totalMs) * 100.0f);

                // Histogramme comparatif simple (update, render, events)
                float times[3] = { updateMs, renderMs, eventsMs };
                ImGui::PlotHistogram("##framebreakdown", times, 3, 0, nullptr, 0.0f, maxFrame, ImVec2(-1, 80));
            }
		}

		void UpdateProfilingData(const ProfilingData& data)
		{
			m_ProfilingData = data;
		}

	private:
		ProfilingData m_ProfilingData;
	};
}