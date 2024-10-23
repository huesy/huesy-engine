#include "engine/logging.h"
#include "engine/renderer.h"
#include "engine/window.h"
#include <SDL3/SDL.h>

EngineResult
renderer_system_init(RendererSystem *system,
		Window *window,
		const RendererSystemConfig *config)
{
	system->handle = SDL_CreateRenderer((SDL_Window *)window->handle, NULL);

	if (system->handle == NULL) {
		log_error("Failed to create SDL renderer: %s", SDL_GetError());
		return ENGINE_ERROR;
	}

	if (config->vsyncEnabled) {
		SDL_SetRenderVSync(system->handle, 1);
	}

	SDL_SetRenderDrawColor(system->handle, 0, 0, 0, 255);

	log_info("Renderer system initialized.");

	return ENGINE_SUCCESS;
}

void
renderer_system_shutdown(RendererSystem *system)
{
	SDL_DestroyRenderer((SDL_Renderer *)system->handle);
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
