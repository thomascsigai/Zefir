#include <ResourceManager.h>
#include <Log.h>

namespace Djipi
{
	ResourceManager::ResourceManager(bool preloadAll) : m_PreloadAll(preloadAll)
	{
		if (m_PreloadAll)
		{
			if (!LoadAllResources())
			{
				LOG_WARN("Unable to preload all resources.");
			}
			else
			{
				LOG_INFO("All resources preloaded.")
			}
		}
	}

	ResourceManager::~ResourceManager()
	{
		UnloadAllResources();
	}

	bool ResourceManager::LoadAllResources()
	{
		return true;
	}

	bool ResourceManager::UnloadAllResources()
	{
		return true;
	}

	bool ResourceManager::LoadResource(const std::string& path)
	{
		if (m_Textures.count(path))
		{
			LOG_WARN("Trying to load an already loaded resource : " + path);
		}

		return true;
	}

	bool ResourceManager::UnloadResource(const std::string& path)
	{
		return true;
	}

	bool ResourceManager::ReloadResource(const std::string& path)
	{
		return true;
	}

	/*const Resource& ResourceManager::GetResource(const std::string& path) const
	{
		return ;
	}*/
}