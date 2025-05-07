#pragma once

#include <Log.h>

namespace Zefir
{
	class PhysicsEngine
	{
	public:
		PhysicsEngine()
		{
			Init();
		}
		~PhysicsEngine()
		{
			Shutdown();
		}

	private:
		bool Init()
		{
			LOG_INFO("Physics engine initialized.");
			return true;
		}
		void Shutdown()
		{

		}
	};
}