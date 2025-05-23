#pragma once

#include <iostream>
#include <SDL.h>

/*
* This header defines macros that can be used to log info into
* the console from the engine and the app.
*/

#ifndef NDEBUG

// Engine logging
#define LOG_INFO(str)		std::cout << "[ZEFIR][INFO] : " << str << std::endl;
#define LOG_WARN(str)		std::cout << "\x1B[33m" << "[ZEFIR][WARN] : " << str << "\033[0m\t\t"  << std::endl;
#define LOG_FATAL(str)		std::cout << "\x1B[31m" << "[ZEFIR][FATAL] : " << str << "\033[0m\t\t" << std::endl;

// App logging
#define APP_LOG_INFO(str)	Zefir::SendAppLog(str, 0);
#define APP_LOG_WARN(str)	Zefir::SendAppLog(str, 1);
#define APP_LOG_FATAL(str)	Zefir::SendAppLog(str, 2);

#else
// If not debug, the macro does nothing
#define LOG_INFO(str) {}
#define LOG_WARN(str) {}
#define LOG_FATAL(str) {}

#define APP_LOG_INFO(str) {}
#define APP_LOG_WARN(str) {}
#define APP_LOG_FATAL(str) {}

#endif

namespace Zefir
{
	const inline Uint32 APP_LOG = SDL_RegisterEvents(1);

	/// Push an event to event queue to request log printing with log message and
	/// severity code :
	/// 0: INFO
	/// 1: WARN
	/// 2: FATAL
	static void SendAppLog(const std::string& msg, int severity)
	{
		SDL_Event e;
		SDL_zero(e);
		e.user.type = APP_LOG;
		e.user.data1 = new std::string(msg);
		e.user.data2 = new int(severity);
		SDL_PushEvent(&e);
	}
}