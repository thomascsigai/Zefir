#pragma once

#include <memory>
#include <string>

#include <json.hpp>

#include <sstream>
#include <fstream>

namespace Zefir
{
	struct MetaData
	{
		virtual ~MetaData() = default;
	};

	class IParser
	{
	public:
		virtual std::shared_ptr<MetaData> Parse(const std::string& path) = 0;
		virtual ~IParser() = default;
	};
}