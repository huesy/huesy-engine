#include <engine/application.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	Application app = {0};

	ApplicationConfig config = {};

	config.memory.poolSize = 1024 * 1024 * 512; // 64 MB memory pool.

	config.window.width = 1280;
	config.window.height = 720;
	config.window.fullScreen = false;

	config.renderer.width = 1920;
	config.renderer.height = 720;
	config.renderer.vsyncEnabled = true;

	// Initialize the application with the config.
	if (application_init(&app, &config) != ENGINE_SUCCESS) {
		log_error("Application initialization failed.");
		return 1;
	}

	// Main game loop.
	b8 isRunning = true;
	while (isRunning) {
		platform_poll_events(app.platform);
		// Update game systems.
		renderer_system_clear(app.renderer);
		// Render game systems.
		renderer_system_present(app.renderer);
		platform_sleep_to_control_fps(app.platform, 60);
		isRunning = platform_is_running(app.platform);
	}

	memory_system_print_stats(app.memory);

	// Shutdown the application.
	application_shutdown(&app);

	return 0;
}
