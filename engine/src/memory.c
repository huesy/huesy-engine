#include "engine/memory.h"
#include "engine/platform.h"

EngineResult
memory_system_init(MemorySystem *system, const MemorySystemConfig *config)
{
	// TODO: Implement memory system initialization.
	// memory->poolSize = config->poolSize;
	// memory->pool = platform_memory_allocate(memory->poolSize);
	// if (memory->pool == NULL) {
	// 	return ENGINE_ERROR;
	// }

	return ENGINE_SUCCESS;
}

void
memory_system_shutdown(MemorySystem *system)
{
	// platform_memory_free(memory->pool);
}

void *
memory_system_allocate(MemorySystem *system, u64 size)
{
	return platform_memory_allocate(size);
}

void
memory_system_free(MemorySystem *system, void *ptr)
{
	platform_memory_free(ptr);
}
