#include <engine/application.h>
#include <stdio.h>

// Game state.
typedef struct GameState {
	f64 playerX;
	f64 playerY;
} GameState;

static GameState gameState = {0};

// Game update function.
static void
game_update(Application *app, f64 deltaTime)
{
	gameState.playerX += 1.0 * deltaTime;

	// We can access engine systems through the app pointer.
	// For example: app->renderer, app->input, etc.
}

// Game render function.
static void
game_render(Application *app, f64 alpha)
{
	renderer_system_clear(app->renderer);
	// TODO: Implement rendering here.
	// NOTE: alpha is the interpolation factor between the current and previous
	// frame.
	renderer_system_present(app->renderer);
}

int
main(int argc, char *argv[])
{
	Application app = {0};

	ApplicationConfig config = {
			.memory.poolSize = 1024 * 1024 * 512, // 64 MB memory pool.

			.window.width = 1280,
			.window.height = 720,
			.window.fullScreen = false,

			.renderer.width = 1280,
			.renderer.height = 720,
			.renderer.vsyncEnabled = true,
			.renderer.targetFrameRate = 60.0,

			.game.targetFrameRate = 60.0,
			.game.initialState = &gameState,
			.game.stateSize = sizeof(GameState),

	};

	// Initialize the application with the config.
	if (application_init(&app, &config) != ENGINE_SUCCESS) {
		log_error("Application initialization failed.");
		return 1;
	}

	// Run the application.
	application_run(&app);

	memory_system_print_stats(app.memory);
	application_shutdown(&app);

	return 0;
}
