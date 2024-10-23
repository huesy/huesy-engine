#ifndef ENGINE_PLUGIN_H
#define ENGINE_PLUGIN_H

#include "engine/defines.h"

typedef struct Plugin {
	const char *name;
	u32 version;

	// Lifecycle callbacks.
	b8 (*initialize)(struct Application *app, const void *config);
	void (*shutdown)(struct Application *app);

	// Core loop callbacks.
	void (*fixedUpdate)(struct Application *app, f64 deltaTime);
	void (*update)(struct Application *app, f64 deltaTime);
	void (*render)(struct Application *app, f64 alpha);

	// Event callbacks.
	void (*onResize)(struct Application *app, u32 width, u32 height);
	void (*onFocus)(struct Application *app, b8 isFocused);
	void (*onMinimize)(struct Application *app, b8 isMinimized);
	void (*onRestore)(struct Application *app);

	// Plugin-specific data.
	void *instance;
	void *api; // Plugin-specific API functions.
} Plugin;

typedef struct PluginSystem {
	Plugin *plugins;
	u32 count;
	u32 capacity;
} PluginSystem;

#endif // ENGINE_PLUGIN_H
