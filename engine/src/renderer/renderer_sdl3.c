#include "engine/logging.h"
#include "engine/platform.h"
#include "engine/renderer.h"
#include <SDL3/SDL.h>

EngineResult
renderer_create(Renderer *renderer, const RendererConfig *config)
{
	renderer->handle = SDL_CreateRenderer((SDL_Window *)config->context, NULL);
	if (renderer->handle == NULL) {
		log_error("Unable to create renderer: %s", SDL_GetError());
		return ENGINE_ERROR;
	}

	return ENGINE_SUCCESS;
}

void
renderer_destroy(Renderer *renderer)
{
	SDL_DestroyRenderer(renderer->handle);
}
