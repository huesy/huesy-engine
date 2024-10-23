#include "engine/application.h"
#include "engine/engine.h"
#include "engine/logging.h"
#include "engine/memory.h"
#include "engine/platform.h"
#include "engine/renderer.h"
#include "engine/window.h"
#include <stdlib.h>

EngineResult
application_init(Application *app, const ApplicationConfig *config)
{
	// Memory system must be initialized first.
	if (memory_system_init(&app->memory, &config->memory) != ENGINE_SUCCESS) {
		log_error("Memory system initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Initialize platform.
	if (platform_init(app, &config->platform) != ENGINE_SUCCESS) {
		log_error("Platform initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Initialize engine.
	if (engine_init(app, &config->engine) != ENGINE_SUCCESS) {
		log_error("Engine initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Create the window.
	if (window_create(app, &config->window) != ENGINE_SUCCESS) {
		log_error("Window creation failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Initialize the renderer.
	if (renderer_system_init(app, &config->renderer) != ENGINE_SUCCESS) {
		log_error("Renderer initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Initialize application state.
	app->state.isInitialized = false;
	app->state.isRunning = false;

	// Initialize the loop state.
	app->state.loop.targetFrameRate = config->engine.targetFrameRate;
	app->state.loop.targetFrameTime = 1.0f / app->state.loop.targetFrameRate;
	app->state.loop.accumulator = 0.0f;
	app->state.loop.frameTime = 0.0f;
	app->state.loop.lastTime = platform_get_absolute_time(app->platform);
	app->state.loop.alpha = 0.0f;
	app->state.loop.fps = 0;
	app->state.loop.frameCount = 0;
	app->state.loop.fpsLastTime = app->state.loop.lastTime;

	// Initialize the application interface.
	if (app->interface && app->interface->state &&
			app->interface->stateSize > 0) {
		app->interface->state =
				memory_system_allocate(app->memory, app->interface->stateSize);
		if (!app->interface->state) {
			log_error("Failed to allocate application interface state memory.");
			application_shutdown(app);
			return ENGINE_ERROR_ALLOCATION_FAILED;
		}
	}

	app->state.isInitialized = true;
	app->state.isRunning = true;

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
	if (app->renderer) {
		renderer_system_shutdown(
				app->renderer); // Renderer shutdown before window.
	}

	if (app->window) {
		platform_window_destroy(app);
	}

	if (app->engine) {
		engine_shutdown(app->engine);
	}

	if (app->platform) {
		platform_shutdown(app->platform);
	}

	// Memory system should be shutdown last
	if (app->memory) {
		memory_system_shutdown(app->memory);
		// Note: memory system handles freeing its own memory in shutdown
	}
}

void
application_run(Application *app)
{
	if (!app->state.isInitialized || !app->interface) {
		log_error("Application is not properly initialized.");
		return;
	}

	const f64 MAX_DELTA_TIME =
			0.25f; // Maximum time step (prevents spiral of death)
	ApplicationLoopState *loop = &app->state.loop;
	f64 lastTime = platform_get_absolute_time(app->platform);

	while (app->state.isRunning) {
		// Timing
		u64 currentTime = platform_get_absolute_time(app->platform);
		f64 deltaTime = (currentTime - loop->lastTime) / 1000.0f;
		loop->lastTime = currentTime;

		// Clamp maximum frame time.
		if (deltaTime > MAX_DELTA_TIME) {
			deltaTime = MAX_DELTA_TIME;
		}

		// Accumulate time for fixed timestep updates.
		loop->accumulator += deltaTime;

		// Process input.
		platform_poll_events(app->platform);
		app->state.isRunning = platform_is_running(app->platform);

		// Fixed timestep updates. This is the core game loop that updates
		// the game state at a fixed timestep.
		while (loop->accumulator >= loop->targetFrameTime) {
			if (app->interface->update) {
				app->interface->update(app, loop->targetFrameTime);
			}
			loop->accumulator -= loop->targetFrameTime;
		}

		// Calculate interpolation factor. This is used to blend the current
		// frame with the previous frame to create a smooth animation.
		loop->alpha = loop->accumulator / loop->targetFrameTime;

		// Render.
		if (app->interface->render) {
			app->interface->render(app, loop->alpha);
		}

		// FPS counter.
		loop->frameCount++;
		if (currentTime - loop->fpsLastTime >= 1000) {
			// Update FPS every second
			loop->fps = loop->frameCount;
			loop->frameCount = 0;
			loop->fpsLastTime = currentTime;
			log_info("FPS: %d", loop->fps);
		}

		// If vsync is disabled, manually control frame rate.
		if (!app->renderer->isVsyncEnabled) {
			u64 frameEndTime = platform_get_absolute_time(app->platform);
			u64 frameTime = frameEndTime - currentTime;
			u64 targetFrameTime = (u64)(loop->targetFrameTime * 1000.0f);

			if (frameTime < targetFrameTime) {
				platform_sleep(app->platform, targetFrameTime - frameTime);
			}
		}
	}
}
