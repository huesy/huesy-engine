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

typedef struct RendererConfig {
	struct Platform *platform;
} RendererConfig;

typedef struct Renderer {
	void *handle;
} Renderer;

EngineResult renderer_create(Renderer *renderer, const RendererConfig *config);
void renderer_destroy(Renderer *renderer);

#endif // ENGINE_RENDERER_H
