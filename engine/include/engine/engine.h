#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "defines.h"

// The configuration for the engine.
typedef struct EngineConfig {
	// TODO: Add engine configuration.
} EngineConfig;

// The engine state.
typedef struct Engine {
	b8 isInitialized;
	b8 isRunning;
} Engine;

EngineResult engine_init(struct Application *app, const EngineConfig *config);
void engine_shutdown(struct Application *app);
void engine_run(Engine *engine);

#endif // ENGINE_ENGINE_H
