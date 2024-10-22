#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "defines.h"

// The configuration for the engine.
typedef struct EngineConfig {
	struct Platform *platform;
	struct Renderer *renderer;
} EngineConfig;

// The engine state.
typedef struct Engine {
	b8 isRunning;
	struct Platform *platform;
	struct Renderer *renderer;
} Engine;

int engine_init(Engine *engine, const EngineConfig *config);
void engine_shutdown(Engine *engine);

void engine_run(Engine *engine);

#endif // ENGINE_ENGINE_H
