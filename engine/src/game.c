#include "engine/game.h"
#include "engine/application.h"
#include "engine/logging.h"

EngineResult
game_init(Application *app, const GameConfig *config)
{
	app->game = memory_system_allocate(app->memory, sizeof(Game));
	if (!app->game) {
		log_error("Failed to allocate memory for game.");
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	Game *game = app->game;
	game->state.isInitialized = false;
	game->state.isRunning = false;

	// Initialize game loop state.
	game->state.loop.targetFrameRate = config->targetFrameRate;
	game->state.loop.targetFrameTime = 1.0f / game->state.loop.targetFrameRate;
	game->state.loop.accumulator = 0.0f;
	game->state.loop.frameTime = 0.0f;
	game->state.loop.lastTime = platform_get_absolute_time(app->platform);
	game->state.loop.alpha = 0.0f;
	game->state.loop.fps = 0;
	game->state.loop.frameCount = 0;

	// Initialize game-specific state if provided.
	if (config->initialState && config->stateSize > 0) {
		game->state.userData =
				memory_system_allocate(app->memory, config->stateSize);
		if (!game->state.userData) {
			log_error("Failed to allocate memory for game state.");
			return ENGINE_ERROR;
		}
		memory_system_copy(app->memory, game->state.userData,
				config->initialState, config->stateSize);
	}

	game->state.isInitialized = true;
	game->state.isRunning = true;

	log_info("Game initialized successfully.");
	return ENGINE_SUCCESS;
}

void
game_shutdown(Application *app)
{
	if (!app->game) {
		return;
	}

	if (app->game->state.userData) {
		memory_system_free(app->memory, app->game->state.userData);
	}

	memory_system_free(app->memory, app->game);
	app->game = NULL;

	log_info("Game shutdown successfully.");
}
