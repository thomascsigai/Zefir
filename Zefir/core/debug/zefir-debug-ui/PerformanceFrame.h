#pragma once

#include <core/debug/ImGuiManager.h>

namespace Zefir
{
	struct PerformanceFrame : public ImGuiFrame
	{
		std::string GetName() const override
		{
			return ("Performance");
		}

		void ShowContent() const override
		{
			ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
			ImGui::Text("Delta Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
		}
	};
}