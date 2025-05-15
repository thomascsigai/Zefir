#pragma once

#include <core/app/Application.h>

namespace Zefir
{
	class Engine
	{
	public:
		Engine() = default;
		
		void Run(Application& app)
		{
			app.Init();

			while (app.IsRunning())
			{
				//app.OnEvent();
				app.Update();
			}

			app.Exit();
		}
	};
}