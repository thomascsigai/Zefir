#pragma once

#include <iostream>

/*
* This header defines macros that can be used to log info into
* the console from the engine and the app.
*/

#ifndef NDEBUG

// Engine logging
#define LOG_INFO(str) std::cout << "[ZEFIR][INFO] : " << str << std::endl;
#define LOG_WARN(str) std::cout << "[ZEFIR][WARN] : " << str << std::endl;
#define LOG_FATAL(str) std::cout << "[ZEFIR][FATAL] : " << str << std::endl;

// App logging
#define APP_LOG_INFO(str) std::cout << "[APP][INFO] : " << str << std::endl;
#define APP_LOG_WARN(str) std::cout << "[APP][WARN] : " << str << std::endl;
#define APP_LOG_FATAL(str) std::cout << "[APP][FATAL] : " << str << std::endl;

#else
// If not debug, the macro does nothing
#define LOG_INFO(str) {}
#define LOG_WARN(str) {}
#define LOG_FATAL(str) {}

#define APP_LOG_INFO(str) {}
#define APP_LOG_WARN(str) {}
#define APP_LOG_FATAL(str) {}

#endif