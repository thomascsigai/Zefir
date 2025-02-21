#pragma once

#include <iostream>
#include <SDL.h>

#include <Resource.h>
#include <Log.h>

namespace Djipi
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(std::string path) : m_Path(path) {}

		bool Load() override { return false; }
		bool Unload() override { return false; }
		bool Reload() override { return true; }

	private:
		std::string m_Path;
	};
}