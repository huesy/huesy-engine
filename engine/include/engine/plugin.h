#ifndef ENGINE_PLUGIN_H
#define ENGINE_PLUGIN_H

#include "engine/defines.h"

typedef struct Plugin {
	const char *name;
	u32 version;

	// Lifecycle callbacks.
	b8 (*initialize)(struct Application *app);
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

typedef struct PluginSystemConfig {
	u32 capacity;
} PluginSystemConfig;

/**
 * @brief Initialize the plugin system.
 *
 * @param app The application instance.
 * @param config The plugin system configuration.
 * @return ENGINE_SUCCESS if the plugin system was initialized successfully,
 *         otherwise an error code.
 */
EngineResult plugin_system_init(struct Application *app,
		const PluginSystemConfig *config);

/**
 * @brief Shut down the plugin system.
 *
 * @param app The application instance.
 */
void plugin_system_shutdown(struct Application *app);

/**
 * @brief Register a plugin with the system.
 *
 * @param app The application instance.
 * @param plugin The plugin to register.
 * @return ENGINE_SUCCESS if the plugin was registered successfully,
 *         otherwise an error code.
 */
EngineResult plugin_system_register(struct Application *app,
		const Plugin *plugin);

/**
 * @brief Update all plugins.
 *
 * @param app The application instance.
 * @param deltaTime The time since the last update.
 */
void plugin_system_update(struct Application *app, f64 deltaTime);

/**
 * @brief Render all plugins.
 *
 * @param app The application instance.
 * @param alpha The interpolation factor.
 */
void plugin_system_render(struct Application *app, f64 alpha);

#endif // ENGINE_PLUGIN_H
