// Defines application entry point.
//

#include <GameConfig.h>
#include <Zefir.h>

#include <vector>

#include <Player.h>
#include <Ground.h>

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
	Zefir::PhysicsWorld physicsWorld = Zefir::PhysicsWorld();

	Zefir::ResourceManager resourceManager = Zefir::ResourceManager(&renderer);

	Uint64 previousTime = SDL_GetTicks();
	Uint64 currentTime;
	double deltaTime;

	// GAMEOBJECTS
	// Create your gameobjects here

	std::vector<ZefirApp::Player> players;
	players.reserve(100);
	
	for (int i = 0; i < 5; i++)
	{
		players.emplace_back(
			150 * i + 20, 20 * i,
			nullptr,
			nullptr
		);
	}

	for (auto& obj : players)
	{
		physicsWorld.AddObject(&obj);
	}

	ZefirApp::Ground ground = ZefirApp::Ground(100, 500);
	physicsWorld.AddObject(&ground);

	ZefirApp::Ground wall = ZefirApp::Ground(550, 10);
	wall.m_Transform2D.SetSize(30, 500);
	wall.m_BoxCollider.size = { 30, 500 };
	//physicsWorld.AddObject(&wall);

	SDL_Texture* text = nullptr;
	Zefir::LoadText(text, "Zefir Engine", 75, resourceManager, renderer, { 255, 255, 255, 255 });

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
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					int mouseX = e.button.x;
					int mouseY = e.button.y;

					players.emplace_back(
						mouseX, mouseY,
						nullptr,
						nullptr
					);
					physicsWorld.AddObject(&players.back());
				}
			}
			// Handle your events here
			players[3].HandleEvent(e);
		}

		currentTime = SDL_GetTicks();
		deltaTime = (double)(currentTime - previousTime) / 1000;
		previousTime = currentTime;

		// UPDATING
		// Updates methods here

		physicsWorld.Step(deltaTime);
		//player.Update(deltaTime);
		for (auto& player : players)
		{
			player.Update(deltaTime);
		}

		// RENDERING 
		SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(renderer.GetSDLRenderer());
		SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 255, 255, 255);

		// Render all objects in the scene here

		//player.Render(&renderer);
		for (auto& player : players)
		{
			player.Render(&renderer);
		}
		ground.Render(&renderer);
		wall.Render(&renderer);
		Zefir::RenderText(text, renderer, 100, 200);

		SDL_RenderPresent(renderer.GetSDLRenderer());
	}

	SDL_Quit();
	return 0;
}