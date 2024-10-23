#include "engine/memory.h"
#include "engine/plugin.h"

static MemorySystem *system = NULL;

static b8
memory_initialize(Application *app, const void *config)
{
	return memory_system_init(system, config);
}

static void
memory_shutdown(Application *app)
{
	if (system) {
		memory_system_shutdown(system);
		system = NULL;
	}
}

Plugin *
create_memory_plugin(void)
{
	static Plugin plugin = {0};
	plugin.name = "Memory System";
	plugin.version = 1;
	plugin.initialize = memory_initialize;
	plugin.shutdown = memory_shutdown;
	plugin.instance = &system;

	return &plugin;
}
