// Defines application entry point.
//

#include <iostream>
#include <SDL.h>

const std::uint16_t SCREEN_WIDTH = 800;
const std::uint16_t SCREEN_HEIGHT = 600;

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

bool init()
{
	bool success = true;

	// SDL Initialization
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize ! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		//Create Window
		gWindow = SDL_CreateWindow("GameDev QuickStart", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			std::cerr << "Window could not be created ! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			// Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

void close()
{
	// Deallocate surface
	SDL_FreeSurface(gScreenSurface);

	//Destroy Window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argc, char* argv[])
{
	bool quit = false;

	SDL_Event e;

	init();

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
					case SDLK_UP:
					std::cout << "UP pressed" << std::endl;
					break;
					
					case SDLK_DOWN:
					std::cout << "DOWN pressed" << std::endl;
					break;
					
					case SDLK_RIGHT:
					std::cout << "RIGHT pressed" << std::endl;
					break;
					
					case SDLK_LEFT:
					std::cout << "LEFT pressed" << std::endl;
					break;

					default:
					std::cout << "A key is pressed" << std::endl;
					break;
				}
			}
		}
	}

	close();

	return 0;
}