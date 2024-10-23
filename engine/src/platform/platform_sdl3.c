#include "engine/application.h"
#include "engine/logging.h"
#include "engine/memory.h"
#include "engine/platform.h"
#include "engine/window.h"
#include <SDL3/SDL.h>

EngineResult
platform_init(Application *app, const PlatformConfig *config)
{
	app->platform = memory_system_allocate(app->memory, sizeof(Platform));
	if (!app->platform) {
		log_error("Failed to allocate memory for platform.");
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	// TODO: Make flags configurable in the PlatformConfig.
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO)) {
		log_error("SDL initialization failed: %s", SDL_GetError());
		memory_system_free(app->memory, app->platform);
		app->platform = NULL;
		return ENGINE_ERROR;
	}

	app->platform->isRunning = true;
	log_info("Platform system (SDL) initialized successfully.");
	return ENGINE_SUCCESS;
}

void
platform_shutdown(Application *app)
{
	if (!app->platform) {
		return;
	}

	SDL_Quit();
	memory_system_free(app->memory, app->platform);
	app->platform = NULL;
	log_info("Platform system (SDL) shutdown successfully.");
}

EngineResult
platform_window_create(Application *app, const WindowConfig *config)
{
	// Create SDL window.
	app->window->handle =
			SDL_CreateWindow("Huesy Engine", config->width, config->height, 0);

	if (app->window->handle == NULL) {
		log_error("Failed to create platform (SDL) window: %s", SDL_GetError());
		return ENGINE_ERROR;
	}

	log_info("Platform system (SDL) window created successfully.");
	return ENGINE_SUCCESS;
}

void
platform_window_destroy(Application *app)
{
	if (!app->window) {
		return;
	}

	SDL_DestroyWindow((SDL_Window *)app->window->handle);
	log_info("Platform system (SDL) window destroyed successfully.");
	memory_system_free(app->memory, app->window);
	app->window = NULL;
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
platform_sleep(Platform *platform, u32 milliseconds)
{
	SDL_Delay(milliseconds);
}

f64
platform_get_absolute_time(Platform *platform)
{
	return SDL_GetTicks();
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

void
platform_memory_copy(void *dest, const void *src, u64 size)
{
	memcpy(dest, src, size);
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
			SDL_LogMessageV(SDL_LOG_CATEGORY_SYSTEM, SDL_LOG_PRIORITY_CRITICAL,
					format, args);
		} break;

		case LOG_LEVEL_ERROR: {
			SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
					SDL_LOG_PRIORITY_ERROR, format, args);
		} break;

		case LOG_LEVEL_WARNING: {
			SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN,
					format, args);
		} break;

		case LOG_LEVEL_INFO: {
			SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
					format, args);
		} break;

		case LOG_LEVEL_DEBUG: {
			SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
					SDL_LOG_PRIORITY_DEBUG, format, args);
		} break;

		case LOG_LEVEL_TRACE: {
			SDL_LogMessageV(SDL_LOG_CATEGORY_APPLICATION,
					SDL_LOG_PRIORITY_VERBOSE, format, args);
		} break;
	}

	va_end(args);
}

#pragma endregion
