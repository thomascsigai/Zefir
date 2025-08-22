#pragma once

namespace Zefir
{
	struct ProfilingData
	{
		// Time used to render a frame (in ms)
		double renderTime = 0;
		double updateTime = 0;
		double eventHandlingTime = 0;
		double physicsTime = 0;

		ProfilingData() = default;
		ProfilingData(const ProfilingData& data)
		{
			renderTime = data.renderTime;
			updateTime = data.updateTime;
			eventHandlingTime = data.eventHandlingTime;
			physicsTime = data.physicsTime;
		}
	};
}