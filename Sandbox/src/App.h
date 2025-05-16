// Defines application behavior
//

#include <GameConfig.h>
#include <Zefir.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <Player.h>

namespace ZefirApp
{
	class SandboxApp : public Zefir::Application
	{
	public:
		SandboxApp()
			: m_Player(m_ResourceManager.GetTexture("resources\\textures\\player.png"),
				m_ResourceManager.GetAnimatedTexture("resources\\anims\\cat.png"))
		{
			Init();
		}

		void Init() override
		{
			Zefir::LoadText(text, "Zefir Engine", 75, m_ResourceManager, m_Renderer, { 255, 255, 255, 255 });
		}

		void OnEvent(SDL_Event& e) override
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				if (e.key.keysym.sym == SDLK_SPACE)
					m_ResourceManager.ReloadAllResources();
				if (e.key.keysym.sym == SDLK_e)
					m_SoundManager.PlaySound(m_ResourceManager.GetSound("resources\\sounds\\win1.wav"));
				if (e.key.keysym.sym == SDLK_r)
					m_ResourceManager.UnloadAllResources();
			}

			m_Player.HandleEvent(e);
		}

		void Update() override
		{
			m_Player.Update(m_DeltaTime);
		}

		void Render() override
		{
			m_Player.Render(&m_Renderer);
			Zefir::RenderText(text, m_Renderer, 100, 200);
		}


		void Exit() override
		{

		}

	private:
		ZefirApp::Player m_Player;
		SDL_Texture* text = nullptr;
	};
}