#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "defines.h"

struct Application;

// The configuration for the engine.
typedef struct EngineConfig {
	const char *applicationName;
	f64 targetFrameRate;
} EngineConfig;

typedef struct Engine {
	b8 isInitialized;
	b8 isRunning;
	const char *applicationName;
	f64 targetFrameRate;
} Engine;

// Core engine functions.
ENGINE_API EngineResult engine_init(struct Application *app,
		const EngineConfig *config);
ENGINE_API void engine_shutdown(struct Application *app);
ENGINE_API void engine_run(struct Application *app);

#endif // ENGINE_ENGINE_H
