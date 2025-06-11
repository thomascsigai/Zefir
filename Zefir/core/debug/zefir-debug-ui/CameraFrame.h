#pragma once

#include <core/debug/ImGuiManager.h>
#include <core/EngineEvents.h>

namespace Zefir
{
	struct CameraFrame : public ImGuiFrame
	{
		float pos[2] = {};
		float zoom = 0;

		std::string GetName() override
		{
			return ("Camera");
		}

		void ShowContent() override
		{
			if (ImGui::DragFloat2("Position", pos, 0.1f, -1000.0f, 1000.0f, "%.2f"))
			{
				SDL_Event e;
				e.type = EngineEvents::CAMERA_MOVE;
				e.user.data1 = new Vector2(pos[0], pos[1]);
				SDL_PushEvent(&e);
			}

			ImGui::DragFloat("Zoom", &zoom);
		}
	};
}