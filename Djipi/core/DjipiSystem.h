#pragma once

#include <Log.h>

namespace Djipi
{
	class DjipiSystem
	{
	public:
		virtual ~DjipiSystem() {}

	protected:
		virtual bool Init() = 0;
		virtual void Shutdown() = 0;
	};
}