#include "engine/logging.h"
#include "engine/platform.h"
#include <SDL3/SDL.h>

EngineResult
platform_init(Platform *platform, const PlatformConfig *config)
{
	// TODO: Make flags configurable in the PlatformConfig.
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO)) {
		log_error("Unable to initialize SDL: %s", SDL_GetError());
		return ENGINE_FAILURE;
	}

	// Create the window.
	platform->handle =
			SDL_CreateWindow(config->title, config->width, config->height, 0);
	if (platform->handle == NULL) {
		log_error("Unable to create SDL window: %s", SDL_GetError());
		SDL_Quit();
		return ENGINE_FAILURE;
	}

	log_info("SDL initialized successfully.");
	return ENGINE_SUCCESS;
}

void
platform_shutdown(Platform *platform)
{
	SDL_DestroyWindow(platform->handle);
	SDL_Quit();
}

void
platform_poll_events(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT:
				engine_shutdown();
				break;
		}
	}
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
