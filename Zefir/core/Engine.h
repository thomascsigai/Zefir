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
			Uint64 previousTime = SDL_GetTicks();
			Uint64 currentTime;

			SDL_Event e;

			app.Init();

			while (app.IsRunning())
			{
				//app.OnEvent();
				// EVENTS LOOP
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						app.SetIsRunning(false);
					}

					app.OnEvent(e);
				}

				currentTime = SDL_GetTicks();
				app.m_DeltaTime = (double)(currentTime - previousTime) / 1000;
				previousTime = currentTime;

				app.Update();

				// RENDERING 
				SDL_SetRenderDrawColor(app.GetSDLRenderer(), 0, 0, 0, 255);
				SDL_RenderClear(app.GetSDLRenderer());
				SDL_SetRenderDrawColor(app.GetSDLRenderer(), 255, 255, 255, 255);

				app.Render();

				SDL_RenderPresent(app.GetSDLRenderer());
			}

			app.Exit();
			SDL_Quit();
		}


	};
}