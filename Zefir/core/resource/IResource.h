#pragma once

#include <string>
#include <filesystem>

namespace Zefir
{
	class IResource
	{
	public:
		IResource() = default;

		virtual bool Load() = 0;
		virtual bool Unload() = 0;
		virtual bool Reload() = 0;

	};
}