/**
 * @file renderer.h
 * @brief Renderer for the engine.
 * @author Andrew Hughes
 * @version 0.1
 * @date 2024-10-21
 * @copyright Huesy Engine is Copyright (c) 2024 Andrew Hughes
 */

#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include "engine/defines.h"
#include "engine/window.h"

typedef struct RendererSystemConfig {
	u32 width;		 // Resolution width.
	u32 height;		 // Resolution height.
	b8 vsyncEnabled; // Enable vertical sync.
	void *context;	 // Platform-specific context.
} RendererSystemConfig;

typedef struct RendererSystem {
	void *handle; // Platform-specific renderer handle.
} RendererSystem;

/**
 * @brief Initializes the renderer system.
 *
 * @param system A pointer to the renderer instance.
 * @param window A pointer to the platform-specific window.
 * @param config A pointer to the renderer configuration.
 * @return EngineResult
 */
EngineResult renderer_system_init(RendererSystem *system,
		Window *window,
		const RendererSystemConfig *config);

/**
 * @brief Shuts down the renderer system.
 *
 * @param system A pointer to the renderer instance to destroy.
 */
void renderer_system_shutdown(RendererSystem *system);

/**
 * @brief Clear the renderer.
 *
 * @param system A pointer to the renderer instance.
 */
void renderer_system_clear(RendererSystem *system);

/**
 * @brief Present the renderer.
 *
 * @param system A pointer to the renderer instance.
 */
void renderer_system_present(RendererSystem *system);

#endif // ENGINE_RENDERER_H
