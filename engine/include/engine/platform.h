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

/**
 * @brief Initialize the platform.
 *
 * @param app The application instance.
 * @param config The platform configuration.
 * @return EngineResult
 */
EngineResult platform_init(struct Application *app,
		const PlatformConfig *config);

/**
 * @brief Shutdown the platform.
 *
 * @param app The application instance.
 */
void platform_shutdown(struct Application *app);

/**
 * @brief Create a window.
 *
 * @param app The application instance.
 * @param config The window configuration.
 * @return EngineResult
 */
EngineResult platform_window_create(struct Application *app,
		const WindowConfig *config);

/**
 * @brief Destroy a window.
 *
 * @param app The application instance.
 */
void platform_window_destroy(struct Application *app);

/**
 * @brief Poll events for the platform.
 *
 * @param platform The platform instance.
 */
void platform_poll_events(Platform *platform);

/**
 * @brief Check if the platform is running.
 *
 * @param platform The platform instance.
 * @return b8 True if the platform is running, false otherwise.
 */
b8 platform_is_running(Platform *platform);

/**
 * @brief Sleep for a given amount of time in milliseconds.
 *
 * @param platform The platform instance.
 * @param milliseconds The amount of time to sleep in milliseconds.
 */
void platform_sleep(Platform *platform, u32 milliseconds);

/**
 * @brief Get the absolute time in milliseconds.
 *
 * @param platform The platform instance.
 * @return f64 The absolute time in milliseconds.
 */
f64 platform_get_absolute_time(Platform *platform);

// ============================================================================
#pragma region Memory

/**
 * @brief Allocate memory.
 *
 * @param size The size of the memory to allocate.
 * @return void* A pointer to the allocated memory.
 */
ENGINE_API void *platform_memory_allocate(u64 size);

/**
 * @brief Free memory.
 *
 * @param ptr A pointer to the memory to free.
 */
ENGINE_API void platform_memory_free(void *ptr);

/**
 * @brief Copy memory from one location to another.
 *
 * @param dest The destination pointer.
 * @param src The source pointer.
 * @param size The size of the memory to copy.
 */
ENGINE_API void platform_memory_copy(void *dest, const void *src, u64 size);

#pragma endregion Memory
// ============================================================================

#endif // ENGINE_PLATFORM_H
