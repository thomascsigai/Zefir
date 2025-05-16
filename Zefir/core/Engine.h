#pragma once

#include <core/app/Application.h>

namespace Zefir
{
	class Engine
	{
	public:
		Engine() = default;
		
		void Run(Application& app)
		{
			if (!app.Init())
			{
				LOG_FATAL("Application could not be initialized.");
			}

			int previousTime = SDL_GetTicks();
			int currentTime;

			SDL_Event e;

			while (app.IsRunning())
			{
				app.OnEvent(e);
				
				currentTime = SDL_GetTicks();
				app.m_DeltaTime = (double)(currentTime - previousTime) / 1000;
				previousTime = currentTime;

				app.Update();
				app.Render();
			}

			app.Exit();
		}
	};
}