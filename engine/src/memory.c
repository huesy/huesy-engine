#include "engine/memory.h"
#include "engine/platform.h"

void *
memory_allocate(u64 size)
{
	return platform_memory_allocate(size);
}

void
memory_free(void *ptr)
{
	platform_memory_free(ptr);
}
