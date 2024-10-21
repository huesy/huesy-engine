#include <stdio.h>

int
main(void)
{
	printf("Hello, World!");
	return 0;
}

// #include <SDL3/SDL.h>
// #include <SDL3/SDL_main.h>

// int
// main(int argc, char *argv[])
// {
// 	SDL_Window *window = NULL;
// 	SDL_Renderer *renderer = NULL;

// 	// Initialize SDL.
// 	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
// 		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
// 		return 1;
// 	}

// 	// Create the window.
// 	window = SDL_CreateWindow("Huesy", 800, 600, 0);
// 	if (window == NULL) {
// 		SDL_Log("Unable to create window: %s", SDL_GetError());
// 		return 1;
// 	}

// 	renderer = SDL_CreateRenderer(window, NULL);
// 	if (renderer == NULL) {
// 		SDL_Log("Unable to create renderer: %s", SDL_GetError());
// 		return 1;
// 	}

// 	SDL_Log("SDL initialized successfully.");

// 	SDL_Event event;
// 	int isRunning = 1;

// 	while (isRunning) {
// 		while (SDL_PollEvent(&event)) {
// 			if (event.type == SDL_EVENT_QUIT) {
// 				isRunning = 0;
// 			}
// 		}

// 		SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 255);
// 		SDL_RenderClear(renderer);

// 		SDL_RenderPresent(renderer);
// 		SDL_Delay(16);
// 	}

// 	SDL_Log("SDL shutting down...");

// 	// Clean up.
// 	SDL_DestroyRenderer(renderer);
// 	SDL_DestroyWindow(window);

// 	// Quit SDL.
// 	SDL_Quit();

// 	return 0;
// }
