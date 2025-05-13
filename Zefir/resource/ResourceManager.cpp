#include <resource/ResourceManager.h>
#include <core/debug/Log.h>
#include <GameConfig.h>
#include <resource/types/meta/AnimationMeta.h>

#include <filesystem>

namespace fs = std::filesystem;

namespace Zefir
{
	ResourceManager::ResourceManager(bool preloadAll) : m_PreloadAll(preloadAll)
	{
		m_Renderer = nullptr;
		Init();
	}

	ResourceManager::ResourceManager(Renderer* renderer, bool preloadAll) : m_PreloadAll(preloadAll)
	{
		m_Renderer = renderer;
		Init();
	}

	ResourceManager::~ResourceManager()
	{
		m_Renderer = nullptr;
		Shutdown();
	}
	
	void ResourceManager::Init()
	{
		if (m_PreloadAll)
		{
			if (!LoadAllResources())
			{
				LOG_WARN("Unable to preload all resources.");
			}
			else
			{
				LOG_INFO("All resources preloaded.");
			}
		}
	}

	void ResourceManager::Shutdown()
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

				// Ignore meta files
				if (entry.path().extension().string() == ".meta")
				{
					continue;
				}

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
		int resourcesFound = 0;
		int resourcesUnloaded = 0;
		int resourcesNotUnloaded = 0;

		for (auto& texture : m_Textures)
		{
			resourcesFound++;

			if (UnloadResource(texture.first, false))
			{
				resourcesUnloaded++;
			}
			else
			{
				resourcesNotUnloaded++;
			}
		}

		for (auto& anim : m_AnimatedTextures)
		{
			resourcesFound++;

			if (UnloadResource(anim.first, false))
			{
				resourcesUnloaded++;
			}
			else
			{
				resourcesNotUnloaded++;
			}
		}

		for (auto& sound : m_Sounds)
		{
			resourcesFound++;

			if (UnloadResource(sound.first, false))
			{
				resourcesUnloaded++;
			}
			else
			{
				resourcesNotUnloaded++;
			}
		}

		for (auto& font : m_Fonts)
		{
			resourcesFound++;

			if (UnloadResource(font.first, false))
			{
				resourcesUnloaded++;
			}
			else
			{
				resourcesNotUnloaded++;
			}
		}

		m_Textures.clear();
		m_AnimatedTextures.clear();
		m_Sounds.clear();
		m_Fonts.clear();

		LOG_INFO("Unloading complete. Resources found: " << resourcesFound << " (" << resourcesUnloaded << " unloaded, " << resourcesNotUnloaded << " not unloaded).");
		return true;
	}

	bool ResourceManager::ReloadAllResources()
	{
		int resourcesFound = 0;
		int resourcesReloaded = 0;
		int resourcesNotReloaded = 0;

		for (auto& texture : m_Textures)
		{
			resourcesFound++;

			if (ReloadResource(texture.first))
			{
				resourcesReloaded++;
			}
			else
			{
				resourcesNotReloaded++;
			}
		}

		for (auto& anim : m_AnimatedTextures)
		{
			resourcesFound++;

			if (ReloadResource(anim.first))
			{
				resourcesReloaded++;
			}
			else
			{
				resourcesNotReloaded++;
			}
		}

		for (auto& sound : m_Sounds)
		{
			resourcesFound++;

			if (ReloadResource(sound.first))
			{
				resourcesReloaded++;
			}
			else
			{
				resourcesNotReloaded++;
			}
		}

		for (auto& font : m_Fonts)
		{
			resourcesFound++;

			if (ReloadResource(font.first))
			{
				resourcesReloaded++;
			}
			else
			{
				resourcesNotReloaded++;
			}
		}

		LOG_INFO("Reloading complete. Resources found: " << resourcesFound << " (" << resourcesReloaded << " reloaded, " << resourcesNotReloaded << " not reloaded).");
		return true;
	}

	bool ResourceManager::LoadResource(const std::string& path)
	{
		std::string parentFolder = fs::path(path).parent_path().filename().string();

		// Detect resource type by location in resource dir
		if (parentFolder == RESOURCES_TEXTURES_DIR)
		{
			std::shared_ptr<Texture> texture = std::make_shared<Texture>(path, m_Renderer);
			if (!texture->Load())
			{
				LOG_WARN("Texture " + path + " could not be loaded.");
				return false;
			}
			else
			{
				m_Textures.insert({ path, texture });
				LOG_INFO("Texture " + path + " successfully loaded.");
			}
			
		}
		else if (parentFolder == RESOURCES_ANIM_DIR)
		{
			std::shared_ptr<AnimatedTexture> anim = std::make_shared<AnimatedTexture>(path, m_Renderer);
			if (!anim->Load())
			{
				LOG_WARN("Animated texture " + path + " could not be loaded.");
				return false;
			}
			else
			{
				m_AnimatedTextures.insert({ path, anim });
				LOG_INFO("Animated texture " + path + " successfully loaded.");
			}
		}
		else if (parentFolder == RESOURCES_SOUNDS_DIR)
		{
			std::shared_ptr<Sound> sound = std::make_shared<Sound>(path);
			if (!sound->Load())
			{
				LOG_WARN("Sound " + path + " could not be loaded.");
				return false;
			}
			else
			{
				m_Sounds.insert({ path, sound });
				LOG_INFO("Sound " + path + " successfully loaded.");
			}
		}
		else if (parentFolder == RESOURCES_FONTS_DIR)
		{
			std::shared_ptr<Font> font = std::make_shared<Font>(path);
			if (!font->Load())
			{
				LOG_WARN("Font " + path + " could not be loaded.");
				return false;
			}
			else
			{
				m_Fonts.insert({ path, font });
				LOG_INFO("Font " + path + " successfully loaded.");
			}
		}
		else
		{
			LOG_WARN(path + " could not be loaded. Resource does not exist or is not in valid directory.");
			return false;
		}
		
		return true;
	}

	bool ResourceManager::UnloadResource(const std::string& path, bool erase)
	{
		std::string parentFolder = fs::path(path).parent_path().filename().string();

		// Detect resource type by location in resource dir
		if (parentFolder == RESOURCES_TEXTURES_DIR)
		{
			if (m_Textures.count(path) != 0)
			{
				m_Textures[path]->Unload();
				m_Textures[path] = nullptr;
				
				if (erase)
				{
					m_Textures.erase(path);
				}
			}
		}
		else if (parentFolder == RESOURCES_ANIM_DIR)
		{
			if (m_AnimatedTextures.count(path) != 0)
			{
				m_AnimatedTextures[path]->Unload();
				m_AnimatedTextures[path] = nullptr;

				if (erase)
				{
					m_AnimatedTextures.erase(path);
				}
			}
		}
		else if (parentFolder == RESOURCES_SOUNDS_DIR)
		{
			if (m_Sounds.count(path) != 0)
			{
				m_Sounds[path]->Unload();
				m_Sounds[path] = nullptr;
				
				if (erase)
				{
					m_Sounds.erase(path);
				}
			}
		}
		else if (parentFolder == RESOURCES_FONTS_DIR)
		{
			if (m_Fonts.count(path) != 0)
			{
				m_Fonts[path]->Unload();
				m_Fonts[path] = nullptr;
				
				if (erase)
				{
					m_Sounds.erase(path);
				}
			}
		}
		else
		{
			LOG_WARN(path + " could not be unloaded. Resource does not exist or is not in valid directory.");
			return false;
		}

		LOG_INFO(path + " successfully unloaded.");
		return true;
	}

	bool ResourceManager::ReloadResource(const std::string& path)
	{
		std::string parentFolder = fs::path(path).parent_path().filename().string();

		// Detect resource type by location in resource dir
		if (parentFolder == RESOURCES_TEXTURES_DIR)
		{
			if (!m_Textures[path]->Reload())
			{
				return false;
			}
		}
		else if (parentFolder == RESOURCES_ANIM_DIR)
		{
			if (!m_AnimatedTextures[path]->Reload())
			{
				return false;
			}
		}
		else if (parentFolder == RESOURCES_SOUNDS_DIR)
		{
			if (!m_Sounds[path]->Reload())
			{
				return false;
			}
		}
		else if (parentFolder == RESOURCES_FONTS_DIR)
		{
			if (!m_Fonts[path]->Reload())
			{
				return false;
			}
		}
		else
		{
			LOG_WARN(path + " could not be reloaded. Resource does not exist or is not in valid directory.");
			return false;
		}

		LOG_INFO(path + " successfully reloaded.");
		return true;
	}

	std::shared_ptr<Texture> ResourceManager::GetTexture(const std::string& path)
	{
		if (m_Textures.count(path) != 0)
		{
			return m_Textures[path];
		}
		else
		{
			LOG_WARN(path + " not found. Texture is not loaded or does not exist.")
		}

		return nullptr;
	}

	std::shared_ptr<AnimatedTexture> ResourceManager::GetAnimatedTexture(const std::string& path)
	{
		if (m_AnimatedTextures.count(path) != 0)
		{
			return m_AnimatedTextures[path];
		}
		else
		{
			LOG_WARN(path + " not found. Animated texture is not loaded or does not exist.")
		}

		return nullptr;
	}
	
	std::shared_ptr<Sound> ResourceManager::GetSound(const std::string& path)
	{
		if (m_Sounds.count(path) != 0)
		{
			return m_Sounds[path];
		}
		else
		{
			LOG_WARN(path + " not found. Sound is not loaded or does not exist.")
		}

		return nullptr;
	}

	std::shared_ptr<Font> ResourceManager::GetFont(const std::string& path)
	{
		if (m_Fonts.count(path) != 0)
		{
			return m_Fonts[path];
		}
		else
		{
			LOG_WARN(path + " not found. Font is not loaded or does not exist.")
		}

		return nullptr;
	}
}