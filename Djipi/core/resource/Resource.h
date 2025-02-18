#pragma once

namespace Djipi
{
	class Resource
	{
	public:
		Resource();
		virtual ~Resource();

		virtual bool Load();
		virtual void Unload();
		virtual bool Reload();

	private:
		bool Init();

	};
}