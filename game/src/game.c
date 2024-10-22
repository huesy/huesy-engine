#include <engine/engine.h>
#include <engine/platform.h>
#include <engine/renderer.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	// -------------------------------------------------------------------------
	// Initialize the platform (i.e. windowing system).

	// Platform create info.
	PlatformConfig platformConfig = {0};
	platformConfig.width = 1280;
	platformConfig.height = 720;
	platformConfig.title = "Huesy";

	// Platform state.
	Platform platform = {0};

	if (platform_init(&platform, &platformConfig) != ENGINE_SUCCESS) {
		return 1;
	}

	// -------------------------------------------------------------------------
	// Create the renderer. This is what will render the graphics to the
	// platform.

	// Renderer create info.
	RendererConfig rendererConfig = {0};
	rendererConfig.context = platform.handle;

	// Renderer state.
	Renderer renderer = {0};

	if (renderer_create(&renderer, &rendererConfig) != ENGINE_SUCCESS) {
		platform_shutdown(&platform);
		return 1;
	}

	// -------------------------------------------------------------------------
	// Initialize the engine. This will initialize all underlying systems.

	// Engine create info.
	EngineConfig engineConfig = {0};
	engineConfig.platform = &platform;
	engineConfig.renderer = &renderer;

	// Engine state.
	Engine engine = {0};

	if (engine_init(&engine, &engineConfig) != ENGINE_SUCCESS) {
		renderer_destroy(&renderer);
		platform_shutdown(&platform);
		return 1;
	}

	// -------------------------------------------------------------------------
	// Begin the main loop.

	engine_run(&engine);

	// -------------------------------------------------------------------------
	// Cleanup

	engine_shutdown(&engine);
	renderer_destroy(&renderer);
	platform_shutdopwn(&platform);

	return 0;
}
