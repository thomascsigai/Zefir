#pragma once

#include <string>
#include <filesystem>

namespace Djipi
{
	class Resource
	{
	public:
		Resource() = default;

		virtual bool Load() = 0;
		virtual bool Unload() = 0;
		virtual bool Reload() = 0;

	};
}