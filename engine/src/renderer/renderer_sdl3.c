#include "engine/application.h"
#include "engine/logging.h"
#include "engine/memory.h"
#include "engine/renderer.h"
#include "engine/window.h"
#include <SDL3/SDL.h>

EngineResult
renderer_system_init(Application *app, const RendererSystemConfig *config)
{
	// We require the memory and window systems to be initialized before we can
	// initialize the renderer system.
	if (!app->systems.memory || !app->systems.window) {
		log_error("Memory and window systems must be initialized first.");
		return ENGINE_ERROR;
	}

	// Get the memory system.
	MemorySystem *memorySystem = app->systems.memory;

	// First allocate the memory for the renderer system.
	app->systems.renderer =
			memory_system_allocate(memorySystem, sizeof(RendererSystem));

	if (!app->systems.renderer) {
		log_error("Failed to allocate memory for renderer.");
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	// Then initialize the renderer system.
	RendererSystem *system = app->systems.renderer;
	system->width = config->width;
	system->height = config->height;
	system->vsync = config->vsync;

	// Create the SDL renderer and attach it to the system.
	Window *window = app->systems.window;
	system->handle = SDL_CreateRenderer((SDL_Window *)window->handle, NULL);
	if (system->handle == NULL) {
		log_error("Failed to create SDL renderer: %s", SDL_GetError());
		memory_system_free(memorySystem, system);
		return ENGINE_ERROR;
	}

	// Enable vsync if it is enabled in the config.
	if (config->vsync) {
		SDL_SetRenderVSync(system->handle, 1);
	}

	// Set the draw color to black.
	SDL_SetRenderDrawColor(system->handle, 0, 0, 0, 255);

	log_info("Renderer system initialized successfully.");
	return ENGINE_SUCCESS;
}

void
renderer_system_shutdown(Application *app)
{
	if (!app->systems.renderer) {
		log_warning("Renderer system is not initialized.");
		return;
	}

	RendererSystem *system = app->systems.renderer;

	SDL_DestroyRenderer((SDL_Renderer *)system->handle);
	memory_system_free(app->systems.memory, system);
	app->systems.renderer = NULL;

	log_info("Renderer system shutdown successfully.");
}

void
renderer_system_clear(RendererSystem *system)
{
	SDL_RenderClear((SDL_Renderer *)system->handle);
}

void
renderer_system_present(RendererSystem *system)
{
	SDL_RenderPresent((SDL_Renderer *)system->handle);
}
