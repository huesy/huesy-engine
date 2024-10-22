#include "engine/engine.h"
#include "engine/platform.h"
#include <SDL3/SDL.h>
#include <stdio.h>

ENGINE_API int
engine_init(Engine *engine, const EngineConfig *config)
{
	engine->platform = config->platform;
	engine->renderer = config->renderer;

	return ENGINE_SUCCESS;
}

void
engine_shutdown(Engine *engine)
{
	//
}

void
engine_run(Engine *engine)
{
	engine->isRunning = 1;

	while (engine->isRunning) {
		platform_poll_events(engine->platform);

		// Render the frame.
		// renderer_render_frame(engine->renderer);

		// Present the frame.
		// renderer_present_frame(engine->renderer);

		// Sleep for a bit.
		SDL_Delay(16);

		// Check if the platform is still running.
		// engine->isRunning = platform_is_running(engine->platform);

		// Get the running time.
		}
}

// 	PlatformConfig platformConfig = {0};
// 	Platform platform = {0};

// 	if (platform_init(&platform, &platformConfig) != ENGINE_SUCCESS) {
// 		return 1;
// 	}

// 	SDL_Log("Starting engine initialization...");

// 	SDL_Window *window = NULL;
// 	SDL_Renderer *renderer = NULL;

// 	// Initialize SDL.

// 	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
// 		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
// 		printf("Unable to initialize SDL: %s\n", SDL_GetError());
// 		return 1;
// 	}

// 	SDL_Log("SDL initialized successfully.");

// 	// Create the window.
// 	window = SDL_CreateWindow("Huesy", 800, 600, 0);
// 	if (window == NULL) {
// 		SDL_Log("Unable to create window: %s", SDL_GetError());
// 		printf("Unable to create window: %s\n", SDL_GetError());
// 		SDL_Quit();
// 		return 1;
// 	}

// 	SDL_Log("Window created successfully.");

// 	// Create the renderer.
// 	renderer = SDL_CreateRenderer(window, NULL);
// 	if (renderer == NULL) {
// 		SDL_Log("Unable to create renderer: %s", SDL_GetError());
// 		printf("Unable to create renderer: %s\n", SDL_GetError());
// 		SDL_DestroyWindow(window);
// 		SDL_Quit();
// 		return 1;
// 	}

// 	SDL_Log("Renderer created successfully.");

// 	SDL_Event event;
// 	int isRunning = 1;

// 	SDL_Log("Entering main loop...");

// 	while (isRunning) {
// 		while (SDL_PollEvent(&event)) {
// 			if (event.type == SDL_EVENT_QUIT) {
// 				SDL_Log("Quit event received.");
// 				isRunning = 0;
// 			}
// 		}

// 		SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 255);
// 		SDL_RenderClear(renderer);

// 		SDL_RenderPresent(renderer);
// 		SDL_Delay(16);
// 	}

// 	SDL_Log("Exiting main loop.");

// 	return 0;
// }

// void
// engine_shutdown(void)
// {
// 	SDL_Log("Shutting down engine...");

// 	// Clean up.
// 	SDL_DestroyRenderer(renderer);
// 	SDL_DestroyWindow(window);

// 	// Quit SDL.
// 	SDL_Quit();

// 	SDL_Log("Engine shutdown complete.");
// }
