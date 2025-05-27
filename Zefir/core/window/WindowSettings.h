#pragma once

#include <string>
#include <SDL.h>

namespace Zefir
{
	struct WindowSettings
	{
		std::string title;
		Uint32 width;
		Uint32 height;
		bool vsync;

		WindowSettings(const std::string& title = "Zefir App",
			Uint32 width = 1080,
			Uint32 height = 720,
			bool VSync = true)
			: title(title), width(width), height(height), vsync(VSync)
		{
		}
	};
}