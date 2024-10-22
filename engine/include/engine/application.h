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

typedef struct ApplicationConfig {
	const char *title;
	u32 width;
	u32 height;
} ApplicationConfig;

typedef struct Application {
	struct Engine *engine;
} Application;

EngineResult application_create(Application *application);
void application_destroy(Application *application);

#endif // ENGINE_APPLICATION_H
