#include "engine/application.h"
#include "engine/logging.h"
#include "engine/renderer.h"
#include <SDL3/SDL.h>

EngineResult
renderer_system_init(Application *app, const RendererSystemConfig *config)
{
	app->renderer = memory_system_allocate(app->memory, sizeof(RendererSystem));
	if (!app->renderer) {
		log_error("Failed to allocate memory for renderer.");
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	RendererSystem *system = app->renderer;
	system->width = config->width;
	system->height = config->height;
	system->isVsyncEnabled = config->vsyncEnabled;

	system->handle =
			SDL_CreateRenderer((SDL_Window *)app->window->handle, NULL);
	if (system->handle == NULL) {
		log_error("Failed to create SDL renderer: %s", SDL_GetError());
		memory_system_free(app->memory, system);
		return ENGINE_ERROR;
	}

	if (config->vsyncEnabled) {
		SDL_SetRenderVSync(system->handle, 1);
	}

	SDL_SetRenderDrawColor(system->handle, 0, 0, 0, 255);
	log_info("Renderer system initialized successfully.");
	return ENGINE_SUCCESS;
}

void
renderer_system_shutdown(Application *app)
{
	if (!app->renderer) {
		return;
	}

	SDL_DestroyRenderer((SDL_Renderer *)app->renderer->handle);
	memory_system_free(app->memory, app->renderer);
	app->renderer = NULL;
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
