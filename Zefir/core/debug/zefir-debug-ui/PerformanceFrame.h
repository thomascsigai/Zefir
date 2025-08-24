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

            static constexpr int historySize = 100;
            static float fpsHistory[historySize] = { 0.0f };
            static float avgFPSHistory[historySize] = { 0.0f };
            static float frameTimeHistory[historySize] = { 0.0f };

            static float renderTime = 0.0f;
            static float avgRenderTime = 0.0f;
            static float renderHistory[historySize] = { 0.0f };
            static float renderAvgHistory[historySize] = { 0.0f };

            static float fps = 0.0f;
            static float avgFPS = 0.0f;
            static float frameTimeMs = 0.0f;
            static float deltaTime = 0.0f;

            if (profilingPaused)
            {
                if (ImGui::Button("Resume Profiling")) profilingPaused = false;
            }
            else
            {
                if (ImGui::Button("Pause Profiling")) profilingPaused = true;
            }
            
            // History updates
            if (!profilingPaused)
            {
                frameTimeHistory[fpsIndex] = m_ProfilingData.frameTime;
                fpsHistory[fpsIndex] = 1000.0f / m_ProfilingData.frameTime;
                
                float sumFPS = 0.0f;
                for (float f : fpsHistory) sumFPS += f;
                avgFPS = sumFPS / historySize;
                avgFPSHistory[fpsIndex] = avgFPS;
                
                renderHistory[fpsIndex] = m_ProfilingData.renderTime;
                renderTime = m_ProfilingData.renderTime;
                
                float sumRenderTime = 0.0f;
                for (float f : renderHistory) sumRenderTime += f;
                avgRenderTime = sumRenderTime / historySize;
                renderAvgHistory[fpsIndex] = avgRenderTime;

                fps = fpsHistory[fpsIndex];
                frameTimeMs = frameTimeHistory[fpsIndex];
                deltaTime = m_ProfilingData.deltaTime;

                fpsIndex = (fpsIndex + 1) % historySize;
            }

            ImGui::Separator();

            ImGui::Text("Avg FPS: %.1f", fps, avgFPS);
            ImGui::PlotLines("##avgfps", avgFPSHistory, historySize, fpsIndex, nullptr, 0.0f, 240.0f, ImVec2(-1, 80));

            ImGui::Text("Frame Time: %.3f ms", frameTimeMs);
            ImGui::Text("Delta Time: %.3f s", deltaTime);

            ImGui::Separator();

            // Frame Stats
            if (ImGui::CollapsingHeader("Frame Stats", ImGuiTreeNodeFlags_DefaultOpen))
            {
                static float minFrame = FLT_MAX, maxFrame = 0.0f, avgFrame = 0.0f;
                static float updateMs = 0.0f, renderMs = 0.0f, eventsMs = 0.0f, totalMs = 0.0f;

                if (!profilingPaused)
                {
                    minFrame = FLT_MAX;
                    maxFrame = 0.0f;
                    avgFrame = 0.0f;

                    for (float ft : frameTimeHistory)
                    {
                        minFrame = (ft < minFrame) ? ft : minFrame;
                        maxFrame = (ft > maxFrame) ? ft : maxFrame;
                        avgFrame += ft;
                    }
                    avgFrame /= historySize;

                    updateMs = m_ProfilingData.updateTime;
                    renderMs = m_ProfilingData.renderTime;
                    eventsMs = m_ProfilingData.eventHandlingTime;
                    totalMs = updateMs + renderMs + eventsMs;
                }

                ImGui::Text("Frame Time: Avg %.2f ms | Min %.2f ms | Max %.2f ms", avgFrame, minFrame, maxFrame);

                ImGui::Text("(1) Update: %.3f ms (%.0f%%)", updateMs, (updateMs / totalMs) * 100.0f);
                ImGui::Text("(2) Render: %.3f ms (%.0f%%)", renderMs, (renderMs / totalMs) * 100.0f);
                ImGui::Text("(3) Events: %.3f ms (%.0f%%)", eventsMs, (eventsMs / totalMs) * 100.0f);

                float times[3] = { updateMs, renderMs, eventsMs };
                ImGui::PlotHistogram("##breakdown", times, 3, 0, nullptr, 0.0f, maxFrame, ImVec2(-1, 80));
            }

            // Renderer
            if (ImGui::CollapsingHeader("Renderer", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Text("Draw Calls : %d", m_ProfilingData.drawCallsCount);
                ImGui::Text("Render Time: %.3f ms | Avg %.3f ms", renderTime, avgRenderTime);
                ImGui::PlotLines("##avgrendertime", renderHistory, historySize, fpsIndex, nullptr, 0.0f, 33.3f, ImVec2(-1, 80));
            }

            // Memory
            if (ImGui::CollapsingHeader("Memory", ImGuiTreeNodeFlags_DefaultOpen))
            {
                // Resources allocated
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