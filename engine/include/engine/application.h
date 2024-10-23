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
#include "engine/logging.h"
#include "engine/memory.h"
#include "engine/platform.h"
#include "engine/renderer.h"
#include "engine/window.h"

typedef struct ApplicationConfig {
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
} ApplicationConfig;

typedef struct Application {
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
} Application;

EngineResult application_init(Application *app,
		const ApplicationConfig *config);
void application_shutdown(Application *app);

#endif // ENGINE_APPLICATION_H
