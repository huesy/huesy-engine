#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include "engine/defines.h"

typedef struct GameLoopState {
	f64 targetFrameRate;
	f64 targetFrameTime; // in seconds
	f64 accumulator;	 // for fixed timestep
	f64 frameTime;		 // actual frame time
	u64 lastTime;		 // last frame timestamp
	f64 alpha;			 // interpolation factor

	// Performance metrics
	u32 fps;
	u32 frameCount;
	u64 fpsLastTime;
} GameLoopState;

typedef struct GameState {
	GameLoopState loop;
	b8 isInitialized;
	b8 isRunning;
	void *userData; // Game-specific state
} GameState;

typedef struct GameConfig {
	f64 targetFrameRate;
	void *initialState;
	u64 stateSize;
} GameConfig;

typedef struct Game {
	GameState state;
	void (*update)(f64 deltaTime);
	void (*render)(f64 alpha);
} Game;

ENGINE_API EngineResult game_init(struct Application *app,
		const GameConfig *config);
ENGINE_API void game_shutdown(struct Application *app);

#endif // ENGINE_GAME_H
