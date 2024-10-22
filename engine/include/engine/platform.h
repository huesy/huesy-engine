#ifndef ENGINE_PLATFORM_H
#define ENGINE_PLATFORM_H

#include "engine/defines.h"
#include "engine/window.h"

typedef struct PlatformConfig {
	// TODO: Add platform-specific configuration.
} PlatformConfig;

typedef struct Platform {
	void *windowHandle;
	b8 isRunning;
} Platform;

EngineResult platform_init(Platform *platform, const PlatformConfig *config);
void platform_shutdown(Platform *platform);

EngineResult platform_window_create(Platform *platform,
		Window *window,
		const WindowConfig *config);
void platform_window_destroy(Platform *platform, Window *window);

void platform_poll_events(Platform *platform);
b8 platform_is_running(Platform *platform);
void platform_sleep_to_control_fps(Platform *platform, u32 fps);

// ============================================================================

void *platform_memory_allocate(u64 size);
void platform_memory_free(void *ptr);

#endif // ENGINE_PLATFORM_H
