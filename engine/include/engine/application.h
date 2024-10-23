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
#include "engine/game.h"
#include "engine/logging.h"
#include "engine/memory.h"
#include "engine/platform.h"
#include "engine/renderer.h"
#include "engine/window.h"

typedef struct ApplicationState {
	b8 isInitialized;
	b8 isRunning;
} ApplicationState;

typedef struct ApplicationConfig {
	// Systems configs
	PlatformConfig platform;
	MemorySystemConfig memory;
	EngineConfig engine;
	// EventSystemConfig events;
	WindowConfig window;
	RendererSystemConfig renderer;
	// ECSConfig ecs;
	// InputSystemConfig input;
	// NetworkingSystemConfig networking;
	// ScriptingSystemConfig scripting;
	// SceneSystemConfig scene;
	// AudioSystemConfig audio;
	// PhysicsSystemConfig physics;
	// ResourceSystemConfig resource;
	GameConfig game;
} ApplicationConfig;

typedef struct Application {
	// Systems
	Platform *platform;
	MemorySystem *memory;
	Engine *engine;
	Window *window;
	// EventSystem *events;
	RendererSystem *renderer;
	// ECS *ecs;
	// InputSystem *input;
	// NetworkingSystem *networking;
	// ScriptingSystem *scripting;
	// SceneSystem *scene;
	// AudioSystem *audio;
	// PhysicsSystem *physics;
	// ResourceSystem *resource;
	Game *game;

	// State
	ApplicationState state;
} Application;

ENGINE_API EngineResult application_init(Application *app,
		const ApplicationConfig *config);
ENGINE_API void application_shutdown(Application *app);
ENGINE_API void application_run(Application *app);

#endif // ENGINE_APPLICATION_H
