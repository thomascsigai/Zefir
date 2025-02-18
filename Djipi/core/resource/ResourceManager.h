#pragma once

#include <unordered_map>
#include <string>

#include <Texture.h>

namespace Djipi
{
	class ResourceManager
	{
	public:
		ResourceManager(bool preloadAll = true);
		~ResourceManager();

		bool LoadAllResources();
		bool UnloadAllResources();

		bool LoadResource(const std::string& path);
		bool UnloadResource(const std::string& path);
		bool ReloadResource(const std::string& path);

		//const Resource& GetResource(const std::string& path) const;

	private:
		bool m_PreloadAll;
	
		std::unordered_map<std::string, Texture*> m_Textures;
		std::unordered_map<std::string, Texture*> m_Sounds;
		std::unordered_map<std::string, Texture*> m_Fonts;
	};
}