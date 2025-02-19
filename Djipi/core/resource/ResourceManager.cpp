#include <ResourceManager.h>
#include <Log.h>
#include <GameConfig.h>

#include <filesystem>

namespace fs = std::filesystem;

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
		if (!fs::exists(RESOURCES_BASE_DIR) && !fs::is_directory(RESOURCES_BASE_DIR))
		{
			LOG_WARN("\"resources\" base directory could not be found.");
			return false;
		}

		int filesFound = 0;
		int filesLoaded = 0;
		int filesNotLoaded = 0;

		// Iterate through all resources sub-directories to load the ressources 
		for (const auto& entry : fs::recursive_directory_iterator(RESOURCES_BASE_DIR))
		{
			if (fs::is_regular_file(entry.path()))
			{
				std::string filePath = entry.path().string();
				std::string parentFolder = entry.path().parent_path().filename().string();

				if (!LoadResource(filePath))
				{
					filesNotLoaded++;
				}
				else
				{
					filesLoaded++;
				}
			}
		}
		
		filesFound = filesLoaded + filesNotLoaded;
		LOG_INFO("Files found: " << filesFound << " (" << filesLoaded << " loaded, " << filesNotLoaded << " not loaded).");
		
		// If a file has not been loaded, return false
		return (filesNotLoaded == 0);
	}

	bool ResourceManager::UnloadAllResources()
	{
		return true;
	}

	bool ResourceManager::LoadResource(const std::string& path)
	{
		LOG_INFO("Loaded : " + path);
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