// Defines application entry point.
//

#include <GameConfig.h>
#include <SDL.h>

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
		cerr << "SDL could not initialize ! SDL_Error: " << SDL_GetError() << endl;
	}
	else
	{
		//Create Window
		gWindow = SDL_CreateWindow("GameDev QuickStart", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			cerr << "Window could not be created ! SDL_Error: " << SDL_GetError() << endl;
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
					cout << "UP pressed" << endl;
					break;
					
					case SDLK_DOWN:
					cout << "DOWN pressed" << endl;
					break;
					
					case SDLK_RIGHT:
					cout << "RIGHT pressed" << endl;
					break;
					
					case SDLK_LEFT:
					cout << "LEFT pressed" << endl;
					break;

					default:
					cout << "A key is pressed" << endl;
					break;
				}
			}
		}
	}

	close();

	return 0;
}