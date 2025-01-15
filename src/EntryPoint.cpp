// Defines application entry point.
//

#include <iostream>
#include <SDL.h>

const std::uint16_t SCREEN_WIDTH = 800;
const std::uint16_t SCREEN_HEIGHT = 600;

int main(int argc, char* argv[])
{
	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	// SDL Initialization
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize ! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		//Create Window
		window = SDL_CreateWindow("GameDev QuickStart", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if (window == NULL)
		{
			std::cerr << "Window could not be created ! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			// Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			///Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}
	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}