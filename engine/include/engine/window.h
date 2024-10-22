/**
 * @file window.h
 * @brief Window management for the engine.
 * @author Andrew Hughes
 * @version 0.1
 * @date 2024-10-21
 * @copyright Huesy Engine is Copyright (c) 2024 Andrew Hughes
 */

#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include "engine/defines.h"

typedef struct WindowConfig {
	u32 width;	   // Resolution width.
	u32 height;	   // Resolution height.
	b8 fullScreen; // Full screen mode.
} WindowConfig;

typedef struct Window {
	void *handle; // Platform-specific window handle.
} Window;

#endif // ENGINE_WINDOW_H
