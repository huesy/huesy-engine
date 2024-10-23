#include "engine/application.h"
#include "engine/logging.h"
#include "engine/memory.h"
#include <stdlib.h>

EngineResult
application_init(Application *app, const ApplicationConfig *config)
{
	// Initialize memory system first - it should allocate its own memory
	// internally
	if (memory_system_init(&app->memory, &config->memory) != ENGINE_SUCCESS) {
		log_error("Memory system initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Use memory system for all subsequent allocations
	app->platform = memory_system_allocate(app->memory, sizeof(Platform));
	if (platform_init(app->platform, &config->platform) != ENGINE_SUCCESS) {
		log_error("Platform initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	app->engine = memory_system_allocate(app->memory, sizeof(Engine));
	if (engine_init(app->engine, &config->engine) != ENGINE_SUCCESS) {
		log_error("Engine initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Create the window.
	app->window = memory_system_allocate(app->memory, sizeof(Window));
	if (platform_window_create(app->platform, app->window, &config->window) !=
			ENGINE_SUCCESS) {
		log_error("Window creation failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Initialize the renderer.
	app->renderer = memory_system_allocate(app->memory, sizeof(RendererSystem));
	if (renderer_system_init(app->renderer, app->window, &config->renderer) !=
			ENGINE_SUCCESS) {
		log_error("Renderer initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	return ENGINE_SUCCESS;
}

void
application_shutdown(Application *app)
{
	// networking_shutdown(app->networking);
	// scripting_shutdown(app->scripting);
	// scene_shutdown(app->scene);
	// ecs_shutdown(app->ecs);
	// audio_system_shutdown(app->audio);
	// physics_system_shutdown(app->physics);
	// resource_system_shutdown(app->resource);
	// input_system_shutdown(app->input);
	// event_system_shutdown(app->event);
	if (app->renderer != NULL) {
		renderer_system_shutdown(
				app->renderer); // Renderer shutdown before window.
		memory_system_free(app->memory, app->renderer);
	}

	if (app->window) {
		platform_window_destroy(app->platform, app->window);
		memory_system_free(app->memory, app->window);
	}

	if (app->engine) {
		engine_shutdown(app->engine);
		memory_system_free(app->memory, app->engine);
	}

	if (app->platform) {
		platform_shutdown(app->platform);
		memory_system_free(app->memory, app->platform);
	}

	// Memory system should be shutdown last
	if (app->memory) {
		memory_system_shutdown(app->memory);
		// Note: memory system handles freeing its own memory in shutdown
	}
}
