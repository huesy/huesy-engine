#include <engine/application.h>
#include <stdio.h>

// Game state.
typedef struct GameState {
	f64 playerX;
	f64 playerY;
} GameState;

static GameState gameState = {0};

static b8
game_initialize(Application *app)
{
	// Initialize game systems and state.
	gameState.playerX = 0.0f;
	gameState.playerY = 0.0f;

	return true;
}

static void
game_fixed_update(Application *app, f64 deltaTime)
{
	gameState.playerX += 1.0 * deltaTime;
}

static void
game_update(Application *app, f64 deltaTime)
{
	// Variable timestep updates (input, etc.)
}

// Game render function.
static void
game_render(Application *app, f64 alpha)
{
	renderer_begin_frame(app->systems.renderer);
	// ... rendering code ...
	renderer_end_frame(app->systems.renderer);
}

static void
game_shutdown(Application *app)
{
	// Cleanup game resources.
}

b8
create_application(Application *app, ApplicationConfig *config)
{
	// Set up application callbacks.
	app->initialize = game_initialize;
	app->fixedUpdate = game_fixed_update;
	app->update = game_update;
	app->render = game_render;
	app->shutdown = game_shutdown;
	app->state = &gameState;
	app->stateSize = sizeof(GameState);

	// Configure the application.
	config->window.width = 800;
	config->window.height = 600;

	return true;
}
