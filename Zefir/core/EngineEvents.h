#pragma once

namespace Zefir
{
	namespace EngineEvents
	{
		// Here is a list of customs events used and handled by the engine
		const inline Uint32 PAUSE_SIMULATION = SDL_RegisterEvents(1);
		const inline Uint32 RESUME_SIMULATION = SDL_RegisterEvents(1);
		const inline Uint32 SPEED_UP_SIMULATION = SDL_RegisterEvents(1);
	}
}