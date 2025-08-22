#pragma once

namespace Zefir
{
	namespace EngineEvents
	{
		// Here is a list of customs events used and handled by the engine
		const inline Uint32 PAUSE_SIMULATION = SDL_RegisterEvents(1);
		const inline Uint32 RESUME_SIMULATION = SDL_RegisterEvents(1);
		const inline Uint32 SPEED_UP_SIMULATION = SDL_RegisterEvents(1);

		// Resources Events
		const inline Uint32 LOAD_ALL_RESOURCES = SDL_RegisterEvents(1);
		const inline Uint32 RELOAD_ALL_RESOURCES = SDL_RegisterEvents(1);
		const inline Uint32 UNLOAD_ALL_RESOURCES = SDL_RegisterEvents(1);

		// Camera Events
		const inline Uint32 CAMERA_MOVE = SDL_RegisterEvents(1);
		const inline Uint32 CAMERA_ZOOM = SDL_RegisterEvents(1);

		// Current Loaded Scene Events
		const inline Uint32 SCENE_REMOVE_OBJECT = SDL_RegisterEvents(1);

		// Profiling Events
		const inline Uint32 UPDATE_PROFILING_DATA = SDL_RegisterEvents(1);
	}
}