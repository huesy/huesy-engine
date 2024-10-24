/**
 * @file application.h
 * @brief The application.
 * @author Andrew Hughes
 * @version 0.1
 * @date 2024-10-21
 * @copyright Huesy Engine is Copyright (c) 2024 Andrew Hughes
 */

#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "engine/defines.h"
#include "engine/engine.h"
#include "engine/memory.h"
#include "engine/platform.h"
#include "engine/plugin.h"
#include "engine/renderer.h"
#include "engine/window.h"

typedef struct ApplicationSystems {
	Platform *platform;
	Engine *engine;
	Window *window;
	RendererSystem *renderer;
	MemorySystem *memory;
	PluginSystem *plugin;
} ApplicationSystems;

typedef struct ApplicationLoopState {
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
} ApplicationLoopState;

typedef struct ApplicationState {
	b8 isInitialized;
	b8 isRunning;
	ApplicationLoopState loop;
} ApplicationState;

typedef struct Application {
	// Systems.
	ApplicationSystems systems;

	// Internal engine state
	ApplicationState internalState;

	// Application callbacks.
	b8 (*initialize)(struct Application *app);
	void (*fixedUpdate)(struct Application *app, f64 deltaTime);
	void (*update)(struct Application *app, f64 deltaTime);
	void (*render)(struct Application *app, f64 alpha);
	void (*shutdown)(struct Application *app);

	// Application-specific data.
	void *state;
	u64 stateSize;
} Application;

typedef struct ApplicationConfig {
	// System configurations
	MemorySystemConfig memory;
	PlatformConfig platform;
	EngineConfig engine;
	WindowConfig window;
	RendererSystemConfig renderer;
	PluginSystemConfig plugins;

	// Optional configurations for future systems
	// AudioConfig audio;
	// InputConfig input;
	// NetworkConfig network;
	// PhysicsConfig physics;
	// ResourceConfig resource;
} ApplicationConfig;

ENGINE_API EngineResult application_init(Application *app,
		const ApplicationConfig *config);
ENGINE_API void application_shutdown(Application *app);
ENGINE_API void application_run(Application *app);

#endif // ENGINE_APPLICATION_H
