#pragma once

#include <resource/types/meta/IParser.h>
#include <core/debug/Log.h>

namespace Zefir
{
	struct AnimationData : public MetaData
	{
        std::string name = "AnimationName";
		Uint16 frameCount = 0;
		float frameTime = 0.0f;
		Uint32 frameW = 0;
		Uint32 frameH = 0;
		bool repeat = true;
		bool ended = false;
	};

	class AnimationDataParser : public IParser
	{
	public :
		static bool Parse(AnimationData& meta, const std::string& path)
		{
            std::ifstream file(path);
			nlohmann::json j;

			if (!file.is_open())
			{
				LOG_WARN("Meta file for animation ", path, " does not exist. Create one to use animation.");
				return false;
			}

			try
			{
				file >> j;
			}
			catch (nlohmann::json::parse_error& e)
			{
				LOG_WARN("Invalid meta file for animation ", path, ". Make sure it follow Json syntax.");
				return false;
			}
			
			meta.name = j["name"];
			meta.frameCount = j["frameCount"];
			meta.frameW = j["frameW"];
			meta.frameH = j["frameH"];
			meta.frameTime = j["frameTime"];
			meta.repeat = j["repeat"];

            return true;
		}
	};
}