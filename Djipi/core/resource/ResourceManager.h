#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <Renderer.h>
#include <Texture.h>
#include <Sound.h>
#include <Font.h>

namespace Djipi
{
	class ResourceManager
	{
	public:
		ResourceManager(bool preloadAll = true);
		ResourceManager(Renderer* renderer, bool preloadAll = true);
		~ResourceManager();

		bool LoadAllResources();
		bool UnloadAllResources();
		bool ReloadAllResources();

		bool LoadResource(const std::string& path);
		bool UnloadResource(const std::string& path, bool erase = true);
		bool ReloadResource(const std::string& path);

		std::shared_ptr<Texture> GetTexture(const std::string& path);
		std::shared_ptr<Sound> GetSound(const std::string& path);

	private:
		bool m_PreloadAll;
	
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
		std::unordered_map<std::string, std::shared_ptr<Sound>> m_Sounds;
		std::unordered_map<std::string, std::shared_ptr<Font>> m_Fonts;

		Renderer* m_Renderer;

		void Init();
		void Shutdown();
	};
}