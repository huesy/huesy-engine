#include "engine/application.h"
#include "engine/logging.h"
#include "engine/memory.h"
#include <stdlib.h>

EngineResult
application_init(Application *app, const ApplicationConfig *config)
{
	// Initialize memory system first - it should allocate its own memory
	// internally.
	if (memory_system_init(&app->memory, &config->memory) != ENGINE_SUCCESS) {
		log_error("Memory system initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Use memory system for all subsequent allocations
	if (platform_init(app, &config->platform) != ENGINE_SUCCESS) {
		log_error("Platform initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	if (engine_init(app, &config->engine) != ENGINE_SUCCESS) {
		log_error("Engine initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	// Create the window.
	if (platform_window_create(app, &config->window) != ENGINE_SUCCESS) {
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

	// Initialize the game.
	if (game_init(app, &config->game) != ENGINE_SUCCESS) {
		log_error("Game initialization failed.");
		application_shutdown(app);
		return ENGINE_ERROR;
	}

	return ENGINE_SUCCESS;
}

void
application_shutdown(Application *app)
{
	if (app->game) {
		game_shutdown(app->game);
		memory_system_free(app->memory, app->game);
	}

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
	if (!app->state.isInitialized) {
		log_error("Application is not initialized.");
		return;
	}

	app->state.isRunning = true;

	const f64 MAX_DELTA_TIME =
			0.25f; // Maximum time step (prevents spiral of death)

	GameLoopState *loop = &app->game->state.loop;

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

		// Fixed timestep updates. This is the core game loop that updates the
		// game state at a fixed timestep.
		while (loop->accumulator >= loop->targetFrameTime) {
			if (app->game->update) {
				app->game->update(loop->targetFrameTime);
			}
			loop->accumulator -= loop->targetFrameTime;
		}

		// Calculate interpolation factor. This is used to blend the current
		// frame with the previous frame to create a smooth animation.
		loop->alpha = loop->accumulator / loop->targetFrameTime;

		// Render.
		if (app->game->render) {
			app->game->render(loop->alpha);
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
