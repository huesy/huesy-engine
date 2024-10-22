#include "engine/logging.h"
#include "engine/platform.h"
#include "engine/window.h"
#include <SDL3/SDL.h>

EngineResult
platform_init(Platform *platform, const PlatformConfig *config)
{
	// TODO: Make flags configurable in the PlatformConfig.
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO)) {
		log_error("SDL initialization failed: %s", SDL_GetError());
		return ENGINE_ERROR;
	}

	platform->isRunning = true;
	log_info("SDL initialized successfully.");
	return ENGINE_SUCCESS;
}

void
platform_shutdown(Platform *platform)
{
	SDL_Quit();
}

EngineResult
platform_window_create(Platform *platform,
		Window *window,
		const WindowConfig *config)
{
	// Create SDL window.
	window->handle =
			SDL_CreateWindow("Huesy Engine", config->width, config->height, 0);

	if (window->handle == NULL) {
		log_error("Failed to create SDL window: %s", SDL_GetError());
		return ENGINE_ERROR;
	}

	log_info("SDL window created successfully.");
	return ENGINE_SUCCESS;
}

void
platform_window_destroy(Platform *platform, Window *window)
{
	SDL_DestroyWindow((SDL_Window *)window->handle);
}

b8
platform_is_running(Platform *platform)
{
	return platform->isRunning;
}

void
platform_poll_events(Platform *platform)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT: {
				platform->isRunning = false;
			} break;
		}
	}
}

void
platform_sleep_to_control_fps(Platform *platform, u32 fps)
{
	SDL_Delay(1000 / fps);
}

// ============================================================================
#pragma region Logging

void *
platform_memory_allocate(u64 size)
{
	return SDL_malloc(size);
}

void
platform_memory_free(void *ptr)
{
	SDL_free(ptr);
}

#pragma endregion
// ============================================================================
#pragma region Logging

void
platform_log_message(LogLevel level, const char *format, ...)
{
	va_list args;
	va_start(args, format);

	switch (level) {
		case LOG_LEVEL_FATAL: {
			SDL_LogCritical(SDL_LOG_CATEGORY_SYSTEM, format, args);
		} break;

		case LOG_LEVEL_ERROR: {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, format, args);
		} break;

		case LOG_LEVEL_WARNING: {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, format, args);
		} break;

		case LOG_LEVEL_INFO: {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, format, args);
		} break;

		case LOG_LEVEL_DEBUG: {
			SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, format, args);
		} break;

		default: {
			SDL_Log(format, args);
		} break;
	}

	va_end(args);
}

#pragma endregion
