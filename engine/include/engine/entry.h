#ifndef ENGINE_ENTRY_H
#define ENGINE_ENTRY_H

#include "defines.h"
#include "engine/application.h"
#include "engine/logging.h"

// This function must be implemented by the application.
extern EngineResult create_application(Application *app,
		ApplicationConfig *config);

int
main(int argc, char **argv)
{
	// Default configuration.
	ApplicationConfig config = {0};
	config.memory.poolSize = 1024 * 1024 * 512; // 512MB default.
	config.engine.applicationName = "My Application";
	config.engine.targetFrameRate = 60.0f;
	config.window.width = 1280;
	config.window.height = 720;
	config.window.fullScreen = false;
	config.window.title = "My Application Window";
	config.renderer.width = 1280;
	config.renderer.height = 720;
	config.renderer.vsync = true;

	Application app = {0};

	// Let the application modify the default config.
	if (!create_application(&app, &config)) {
		log_error("Failed to create application.");
		return 1;
	}

	if (application_init(&app, &config) != ENGINE_SUCCESS) {
		log_error("Application initialization failed.");
		return 1;
	}

	application_run(&app);
	application_shutdown(&app);

	return 0;
}

#endif // ENGINE_ENTRY_H
