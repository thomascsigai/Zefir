//// Create Renderer
//m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
//
//if (m_Renderer == NULL)
//{
//	std::cerr << "Renderer could not be created ! SDL_Error: " << SDL_GetError() << std::endl;
//	success = false;
//}
//
//if (TTF_Init() < 0)
//{
//	std::cerr << "SDL_ttf could not initialize : " << TTF_GetError() << std::endl;
//	success = false;
//}
//
////Initialize SDL_mixer
//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
//{
//	std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
//	success = false;
//}