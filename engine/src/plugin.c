#include "engine/plugin.h"
#include "engine/application.h"
#include "engine/logging.h"
#include "engine/memory.h"

EngineResult
plugin_system_init(Application *app, const PluginSystemConfig *config)
{
	PluginSystem *system = &app->systems.plugin;
	system->capacity = config->initialCapacity;
	system->count = 0;
	system->plugins = memory_system_allocate(
			app->systems.memory, sizeof(Plugin) * system->capacity);

	if (!system->plugins) {
		log_error("Failed to allocate memory for the plugin system.");
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	log_info("Plugin system initialized with capacity %u.", system->capacity);
	return ENGINE_SUCCESS;
}

void
plugin_system_shutdown(Application *app)
{
	PluginSystem *system = &app->systems.plugin;

	for (u32 i = 0; i < system->count; ++i) {
		Plugin *plugin = &system->plugins[i];
		if (plugin->shutdown) {
			plugin->shutdown(app);
		}
		if (plugin->instance) {
			memory_system_free(app->systems.memory, plugin->instance);
		}
	}

	memory_system_free(app->systems.memory, system->plugins);
	system->plugins = NULL;
	system->count = 0;
	system->capacity = 0;

	log_info("Plugin system shut down.");
}

EngineResult
plugin_system_register(Application *app, const Plugin *plugin)
{
	PluginSystem *system = &app->systems.plugin;

	if (system->count >= system->capacity) {
		u32 newCapacity = system->capacity * 2;
		Plugin *newPlugins = memory_system_allocate(
				app->systems.memory, sizeof(Plugin) * newCapacity);
		if (!newPlugins) {
			log_error("Failed to allocate memory for the plugin system.");
			return ENGINE_ERROR_ALLOCATION_FAILED;
		}

		// Copy existing plugins to the new array.
		memory_system_copy(app->systems.memory, newPlugins, system->plugins,
				sizeof(Plugin) * system->count);
		memory_system_free(app->systems.memory, system->plugins);
		system->plugins = newPlugins;
		system->capacity = newCapacity;
	}

	// Add the new plugin to the end of the array.
	system->plugins[system->count] = *plugin;
	if (plugin->initialize && !plugin->initialize(app)) {
		log_error("Failed to initialize plugin: %s", plugin->name);
		return ENGINE_ERROR;
	}

	system->count++;
	log_info("Registered plugin: %s", plugin->name);
	return ENGINE_SUCCESS;
}

void
plugin_system_update(Application *app, f64 deltaTime)
{
	PluginSystem *system = &app->systems.plugin;

	// Update all plugins in the system.
	for (u32 i = 0; i < system->count; ++i) {
		Plugin *plugin = &system->plugins[i];
		if (plugin->update) {
			plugin->update(app, deltaTime);
		}
	}
}

void
plugin_system_render(Application *app, f64 alpha)
{
	PluginSystem *system = &app->systems.plugin;

	for (u32 i = 0; i < system->count; ++i) {
		Plugin *plugin = &system->plugins[i];
		if (plugin->render) {
			plugin->render(app, alpha);
		}
	}
}
