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
			Zefir::Window window = Zefir::Window();
			Zefir::Renderer renderer = Zefir::Renderer(&window);
			Zefir::SoundManager soundManager = Zefir::SoundManager();

			Zefir::ResourceManager resourceManager = Zefir::ResourceManager(&renderer);

			Uint64 previousTime = SDL_GetTicks();
			Uint64 currentTime;
			double deltaTime;

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
				}

				currentTime = SDL_GetTicks();
				deltaTime = (double)(currentTime - previousTime) / 1000;
				previousTime = currentTime;

				app.Update();

				// RENDERING 
				SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0, 0, 0, 255);
				SDL_RenderClear(renderer.GetSDLRenderer());
				SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 255, 255, 255);

				SDL_RenderPresent(renderer.GetSDLRenderer());
			}

			app.Exit();

			SDL_Quit();
		}
	};
}