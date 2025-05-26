#pragma once

#include <core/debug/ImGuiManager.h>

namespace Zefir
{
	struct ResourcesFrame : public ImGuiFrame
	{
		int resourcesLoaded = 0;

		std::string GetName() override
		{
			return ("Resources");
		}

		void ShowContent() override
		{
			/* TODO - Link this with resource manager
				ImGui::Text("Resources Loaded : "); ImGui::SameLine();
				ImGui::Text(ToString(resourcesLoaded).c_str());
			*/

			if (ImGui::Button("Load All Assets"))
			{
				SDL_Event e = { EngineEvents::LOAD_ALL_RESOURCES };
				SDL_PushEvent(&e);
			}
			if (ImGui::Button("Unload All Assets"))
			{
				SDL_Event e = { EngineEvents::UNLOAD_ALL_RESOURCES };
				SDL_PushEvent(&e);
			}
			if (ImGui::Button("Reload All Assets"))
			{
				SDL_Event e = { EngineEvents::RELOAD_ALL_RESOURCES };
				SDL_PushEvent(&e);
			}
		}
	};
}