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
	u32 width;			 /**< Resolution width. */
	u32 height;			 /**< Resolution height. */
	b8 vsyncEnabled;	 /**< Enable vertical sync. */
	f64 targetFrameRate; /**< Target frame rate. */
	void *context;		 /**< Platform-specific context. */
} RendererSystemConfig;

typedef struct RendererSystem {
	void *handle;	   /**< Platform-specific renderer handle. */
	b8 isVsyncEnabled; /**< Is vsync enabled. */
	u32 width;		   /**< Resolution width. */
	u32 height;		   /**< Resolution height. */
} RendererSystem;

/**
 * @brief Initializes the renderer system.
 *
 * @param app A pointer to the application instance.
 * @param config A pointer to the renderer configuration.
 * @return EngineResult
 */
EngineResult renderer_system_init(struct Application *app,
		const RendererSystemConfig *config);

/**
 * @brief Shuts down the renderer system.
 *
 * @param app A pointer to the application instance.
 */
void renderer_system_shutdown(struct Application *app);

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
