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
			
			SDL_Event e;

			while (app.IsRunning())
			{
				app.OnEvent(e);
				app.Update();
				app.Render();
			}

			app.Exit();
		}
	};
}