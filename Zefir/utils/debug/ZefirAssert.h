#pragma once

#ifndef NDEBUG

#define ASSERT(expr) \
	if (expr) { } \
	else \
	{ \
		std::cerr << "Assertion not passed." << std::endl; \
		__debugbreak(); \
	}

#else

#define ASSERT(expr) 

#endif