// Defines application entry point.
//

#include <GameConfig.h>
#include <Djipi.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <Player.h>

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		LOG_FATAL("SDL could not initialize ! SDL_Error: " << SDL_GetError());
		return 0;
	}

	bool quit = false;

	SDL_Event e;

	Djipi::Window window = Djipi::Window();
	Djipi::Renderer renderer = Djipi::Renderer(&window);
	Djipi::ResourceManager resourceManager = Djipi::ResourceManager(&renderer);

	Uint64 previousTime = SDL_GetTicks();
	Uint64 currentTime;
	double deltaTime;

	// GAMEOBJECTS
	// Create your gameobjects here
	
	DjipiApp::Player player = DjipiApp::Player();
	player.SetTexture(resourceManager.GetTexture("resources\\textures\\player.png"));

	// GAME LOOP
	while (!quit)
	{
		// EVENTS LOOP
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				if (e.key.keysym.sym == SDLK_SPACE)
					resourceManager.ReloadResource("resources\\textures\\player.png");
			}

			// Handle your events here
			player.HandleEvent(e);
		}

		currentTime = SDL_GetTicks();
		deltaTime = (double)(currentTime - previousTime) / 1000;
		previousTime = currentTime;

		// UPDATING
		// Updates methods here

		player.Update(deltaTime);

		// RENDERING 
		SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(renderer.GetSDLRenderer());
		SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 255, 255, 255);

		// Render all objects in the scene here

		player.Render(renderer.GetSDLRenderer());

		SDL_RenderPresent(renderer.GetSDLRenderer());
	}

	SDL_Quit();
	return 0;
}