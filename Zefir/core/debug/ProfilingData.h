#pragma once

namespace Zefir
{
	struct ProfilingData
	{
		// Time used to render a frame (in ms)
		double frameTime = 0;
		double deltaTime = 0;

		double renderTime = 0;
		int drawCallsCount = 0;
		
		double updateTime = 0;
		double eventHandlingTime = 0;

		ProfilingData() = default;
		ProfilingData(const ProfilingData& data)
		{
			deltaTime = data.deltaTime;
			frameTime = data.frameTime;

			renderTime = data.renderTime;
			drawCallsCount = data.drawCallsCount;

			updateTime = data.updateTime;
			eventHandlingTime = data.eventHandlingTime;
		}
	};
}