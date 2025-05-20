#pragma once

#include <scene/Scene.h>
#include <core/debug/Log.h>

#include <gameobjects/PhysicObject.h>
#include <gameobjects/Ground.h>

namespace ZefirApp
{
	SDL_Texture* text;

	class DefaultScene : public Zefir::Scene
	{
		void OnLoad() override
		{
			physicsWorld = std::make_unique<Zefir::PhysicsWorld>();
			
			ground = std::make_unique<Ground>(100, 500);
			physicsWorld->AddObject(ground.get());

			objects.reserve(100);
			
			for (int i = 0; i < 5; i++)
			{
				objects.emplace_back(std::make_unique<PhysicObject>(150 * i + 20, 20 * i));
				physicsWorld->AddObject(objects[i].get());
			}
		}

		void OnUnload() override
		{
		}

		void OnEvent(const SDL_Event& e) 
		{
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					int mouseX = e.button.x;
					int mouseY = e.button.y;

					objects.emplace_back(std::make_unique<PhysicObject>(mouseX, mouseY));
					physicsWorld->AddObject(objects.back().get());
				}
			}
		}
		
		void Update(double deltaTime) override
		{
			for (auto& object : objects)
			{
				object->Update(deltaTime);
			}

			physicsWorld->Step(deltaTime);
		}

		void Render(const std::unique_ptr<Zefir::Renderer>& renderer) override
		{
			ground->Render(renderer);

			for (auto& object : objects)
			{
				object->Render(renderer);
			}
		}

	private:
		std::vector<std::unique_ptr<ZefirApp::PhysicObject>> objects;
		std::unique_ptr<ZefirApp::Ground> ground;

		std::unique_ptr<Zefir::PhysicsWorld> physicsWorld;
	};
}