#pragma once

#include <core/window/Window.h>
#include <resource/ResourceManager.h>
#include <renderer/Renderer.h>
#include <sound/SoundManager.h>
#include <core/debug/ImGuiManager.h>

namespace Zefir
{
	struct EngineContext
	{
		Window* window = nullptr;
		ResourceManager* resourceManager = nullptr;
		Renderer* renderer = nullptr;
		SoundManager* soundManager = nullptr;
		ImGuiManager* imGuiManager = nullptr;
	};
}