// Defines application behavior
//

#include <Zefir.h>

#include <gameobjects/Player.h>

#include <scenes/DefaultScene.h>
#include <scenes/DefaultScene2.h>

namespace ZefirApp
{
	class SandboxApp : public Zefir::Application
	{
	public:
		SandboxApp()
		{}

		void OnInit() override
		{
			m_SceneManager->LoadScene(std::make_unique<DefaultScene>(), &m_EngineContext);
		}

		void HandleEvents(SDL_Event& e) override
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_1)
				{
					m_SceneManager->LoadScene(std::make_unique<DefaultScene>(), &m_EngineContext);
				}
				if (e.key.keysym.sym == SDLK_2)
				{
					m_SceneManager->LoadScene(std::make_unique<DefaultScene2>(), &m_EngineContext);
				}
			}
		}
	};
}