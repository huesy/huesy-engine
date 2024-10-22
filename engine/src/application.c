#include "engine/application.h"
#include "engine/logging.h"
#include <stdlib.h>

EngineResult
application_init(Application *app, const ApplicationConfig *config)
{
	// Allocate and initialize the platform.
	app->platform = (Platform *)malloc(sizeof(Platform));
	if (platform_init(app->platform, &config->platform) != ENGINE_SUCCESS) {
		log_error("Platform initialization failed.");
		return ENGINE_ERROR;
	}

	// Allocate and initialize the engine.
	app->engine = (Engine *)malloc(sizeof(Engine));
	if (engine_init(app->engine, &config->engine) != ENGINE_SUCCESS) {
		log_error("Engine initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Initialize logging system.
	app->logging = (LoggingSystem *)malloc(sizeof(LoggingSystem));
	if (logging_system_init(app->logging, &config->logging) != ENGINE_SUCCESS) {
		log_error("Logging system initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Initialize memory system.
	app->memory = (MemorySystem *)malloc(sizeof(MemorySystem));
	if (memory_system_init(app->memory, &config->memory) != ENGINE_SUCCESS) {
		log_error("Memory system initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Create the window.
	app->window = (Window *)malloc(sizeof(Window));
	if (platform_window_create(app->platform, app->window, &config->window) !=
			ENGINE_SUCCESS) {
		log_error("Window creation failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Initialize the renderer.
	app->renderer = (RendererSystem *)malloc(sizeof(RendererSystem));
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
		free(app->renderer);
	}

	if (app->memory) {
		memory_system_shutdown(app->memory);
		free(app->memory);
	}

	if (app->logging) {
		logging_system_shutdown(app->logging);
		free(app->logging);
	}

	if (app->engine) {
		engine_shutdown(app->engine);
		free(app->engine);
	}

	if (app->platform) {
		platform_window_destroy(app->platform, app->window);
		free(app->window);
		platform_shutdown(app->platform);
		free(app->platform);
	}
}
