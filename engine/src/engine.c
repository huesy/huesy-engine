#include "engine/engine.h"
#include "engine/application.h"
#include "engine/logging.h"
#include "engine/memory.h"

EngineResult
engine_init(Application *app, const EngineConfig *config)
{
	app->engine = memory_system_allocate(app->memory, sizeof(Engine));
	if (!app->engine) {
		log_error("Failed to allocate memory for engine.");
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	Engine *engine = app->engine;
	engine->isInitialized = false;
	engine->isRunning = true;
	engine->applicationName = config->applicationName;
	engine->targetFrameRate = config->targetFrameRate;

	// TODO: Other engine initialization.

	engine->isInitialized = true;
	log_info("Engine initialization successful.");
	return ENGINE_SUCCESS;
}

void
engine_shutdown(Application *app)
{
	if (!app->engine) {
		return;
	}

	memory_system_free(app->memory, app->engine);
	app->engine = NULL;
	log_info("Engine system shutdown successfully.");
}
