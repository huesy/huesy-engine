#ifndef ENGINE_PLATFORM_H
#define ENGINE_PLATFORM_H

#include "engine/defines.h"

typedef struct PlatformConfig {
	i32 width;
	i32 height;
	const char *title;
} PlatformConfig;

typedef struct Platform {
	void *handle;
} Platform;

// Initialize the platform.
EngineResult platform_init(Platform *platform, const PlatformConfig *config);
// Shutdown the platform.
void platform_shutdown(Platform *platform);

// ============================================================================

// Poll events on the platform.
void platform_poll_events(Platform *platform);
// Check if the platform is running.
b8 platform_is_running(Platform *platform);
// Get the running time of the platform.
u64 platform_get_running_time(Platform *platform);

// ============================================================================
#pragma region Memory

void *platform_memory_allocate(u64 size);
void platform_memory_free(void *ptr);

#pragma endregion
// ============================================================================
#pragma region Logging

void platform_log_message(const char *message);

#pragma endregion

#endif // ENGINE_PLATFORM_H
