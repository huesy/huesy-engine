#include "engine/engine.h"
#include <SDL3/SDL.h>
#include <stdio.h>

int
engine_init(void)
{
	SDL_Log("Starting engine initialization...");

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	// Initialize SDL.

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Log("SDL initialized successfully.");

	// Create the window.
	window = SDL_CreateWindow("Huesy", 800, 600, 0);
	if (window == NULL) {
		SDL_Log("Unable to create window: %s", SDL_GetError());
		printf("Unable to create window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	SDL_Log("Window created successfully.");

	// Create the renderer.
	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		printf("Unable to create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Log("Renderer created successfully.");

	SDL_Event event;
	int isRunning = 1;

	SDL_Log("Entering main loop...");

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				SDL_Log("Quit event received.");
				isRunning = 0;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_Log("Exiting main loop.");

	SDL_Log("Shutting down SDL...");

	// Clean up.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// Quit SDL.
	SDL_Quit();

	SDL_Log("Engine shutdown complete.");

	return 0;
}
