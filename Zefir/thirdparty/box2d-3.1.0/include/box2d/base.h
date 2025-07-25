// SPDX-FileCopyrightText: 2023 Erin Catto
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>

// clang-format off
// 
// Shared library macros
#if defined( _MSC_VER ) && defined( box2d_EXPORTS )
	// build the Windows DLL
	#define BOX2D_EXPORT __declspec( dllexport )
#elif defined( _MSC_VER ) && defined( BOX2D_DLL )
	// using the Windows DLL
	#define BOX2D_EXPORT __declspec( dllimport )
#elif defined( box2d_EXPORTS )
	// building or using the shared library
	#define BOX2D_EXPORT __attribute__( ( visibility( "default" ) ) )
#else
	// static library
	#define BOX2D_EXPORT
#endif

// C++ macros
#ifdef __cplusplus
	#define B2_API extern "C" BOX2D_EXPORT
	#define B2_INLINE inline
	#define B2_LITERAL(T) T
	#define B2_ZERO_INIT {}
#else
	#define B2_API BOX2D_EXPORT
	#define B2_INLINE static inline
	/// Used for C literals like (b2Vec2){1.0f, 2.0f} where C++ requires b2Vec2{1.0f, 2.0f}
	#define B2_LITERAL(T) (T)
	#define B2_ZERO_INIT {0}
#endif
// clang-format on

/**
 * @defgroup base Base
 * Base functionality
 * @{
 */

/// Prototype for user allocation function
/// @param size the allocation size in bytes
/// @param alignment the required alignment, guaranteed to be a power of 2
typedef void* b2AllocFcn( unsigned int size, int alignment );

/// Prototype for user free function
/// @param mem the memory previously allocated through `b2AllocFcn`
typedef void b2FreeFcn( void* mem );

/// Prototype for the user assert callback. Return 0 to skip the debugger break.
typedef int b2AssertFcn( const char* condition, const char* fileName, int lineNumber );

/// This allows the user to override the allocation functions. These should be
/// set during application startup.
B2_API void b2SetAllocator( b2AllocFcn* allocFcn, b2FreeFcn* freeFcn );

/// @return the total bytes allocated by Box2D
B2_API int b2GetByteCount( void );

/// Override the default assert callback
/// @param assertFcn a non-null assert callback
B2_API void b2SetAssertFcn( b2AssertFcn* assertFcn );

/// Version numbering scheme.
/// See https://semver.org/
typedef struct b2Version
{
	/// Significant changes
	int major;

	/// Incremental changes
	int minor;

	/// Bug fixes
	int revision;
} b2Version;

/// Get the current version of Box2D
B2_API b2Version b2GetVersion( void );

/**@}*/

//! @cond

// see https://github.com/scottt/debugbreak
#if defined( _MSC_VER )
#define B2_BREAKPOINT __debugbreak()
#elif defined( __GNUC__ ) || defined( __clang__ )
#define B2_BREAKPOINT __builtin_trap()
#else
// Unknown compiler
#include <assert.h>
#define B2_BREAKPOINT assert( 0 )
#endif

#if !defined( NDEBUG ) || defined( B2_ENABLE_ASSERT )
B2_API int b2InternalAssertFcn( const char* condition, const char* fileName, int lineNumber );
#define B2_ASSERT( condition )                                                                                                   \
	do                                                                                                                           \
	{                                                                                                                            \
		if ( !( condition ) && b2InternalAssertFcn( #condition, __FILE__, (int)__LINE__ ) )                                          \
			B2_BREAKPOINT;                                                                                                       \
	}                                                                                                                            \
	while ( 0 )
#else
#define B2_ASSERT( ... ) ( (void)0 )
#endif

/// Get the absolute number of system ticks. The value is platform specific.
B2_API uint64_t b2GetTicks( void );

/// Get the milliseconds passed from an initial tick value.
B2_API float b2GetMilliseconds( uint64_t ticks );

/// Get the milliseconds passed from an initial tick value. Resets the passed in
/// value to the current tick value.
B2_API float b2GetMillisecondsAndReset( uint64_t* ticks );

/// Yield to be used in a busy loop.
B2_API void b2Yield( void );

/// Simple djb2 hash function for determinism testing
#define B2_HASH_INIT 5381
B2_API uint32_t b2Hash( uint32_t hash, const uint8_t* data, int count );

//! @endcond