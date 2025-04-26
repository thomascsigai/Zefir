// Defines application entry point.
//

#include <GameConfig.h>
#include <Zefir.h>

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

	Zefir::Window window = Zefir::Window();
	Zefir::Renderer renderer = Zefir::Renderer(&window);
	Zefir::SoundManager soundManager = Zefir::SoundManager();

	Zefir::ResourceManager resourceManager = Zefir::ResourceManager(&renderer);

	Uint64 previousTime = SDL_GetTicks();
	Uint64 currentTime;
	double deltaTime;

	// GAMEOBJECTS
	// Create your gameobjects here
	
	ZefirApp::Player player = ZefirApp::Player();
	player.SetTexture(resourceManager.GetAnimatedTexture("resources\\anim\\cat.png"));

	SDL_Texture* text = nullptr;
	SDL_Texture* text2 = nullptr;
	Zefir::LoadText(text, "Text rendering", 75, resourceManager, renderer, { 255, 255, 255, 255 });
	Zefir::LoadText(text2, "Text rendering2", 15, resourceManager, renderer, { 255, 255, 255, 255 });

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
					resourceManager.ReloadAllResources();
				if (e.key.keysym.sym == SDLK_e)
					soundManager.PlaySound(resourceManager.GetSound("resources\\sounds\\win1.wav"));
				if (e.key.keysym.sym == SDLK_r)
					resourceManager.UnloadAllResources();
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
		Zefir::RenderText(text, renderer, 100, 200);
		Zefir::RenderText(text2, renderer, 500, 500);

		SDL_RenderPresent(renderer.GetSDLRenderer());
	}

	SDL_Quit();
	return 0;
}