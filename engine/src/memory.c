#include "engine/memory.h"
#include "engine/logging.h"
#include "engine/platform.h"

EngineResult
memory_system_init(MemorySystem *system, const MemorySystemConfig *config)
{
	system->poolSize = config->poolSize;
	system->pool = platform_memory_allocate(system->poolSize);
	if (system->pool == NULL) {
		log_error("Failed to allocate memory pool.");
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	system->usedMemory = 0;
	system->allocationCount = 0;
	system->freeBlocks = NULL; // Initially there are no free blocks.
	log_info("Memory system initialized with pool size %llu bytes.",
			system->poolSize);

	return ENGINE_SUCCESS;
}

void
memory_system_shutdown(MemorySystem *system)
{
	platform_memory_free(system->pool);
	log_info("Memory system shut down. Total allocations: %u",
			system->allocationCount);
}

void *
memory_system_allocate(MemorySystem *system, u64 size)
{
	// First, check if any free blocks can be re-used.
	MemoryBlock *prev = NULL;
	MemoryBlock *block = system->freeBlocks;
	while (block != NULL) {
		if (block->size >= size) {
			if (prev) {
				prev->next = block->next;
			} else {
				system->freeBlocks = block->next;
			}
			system->usedMemory += block->size;
			system->allocationCount++;
			return block->data;
		}
		prev = block;
		block = block->next;
	}

	// If no suitable free block is found, allocate new memory.
	if (system->usedMemory + size > system->poolSize) {
		log_error("Memory system out of memory.");
		return NULL;
	}

	void *memory = (u8 *)system->pool + system->usedMemory;
	system->usedMemory += size;
	system->allocationCount++;
	return memory;
}

void
memory_system_free(MemorySystem *system, void *ptr)
{
	MemoryBlock *block = (MemoryBlock *)((u8 *)ptr - sizeof(MemoryBlock));
	block->next = system->freeBlocks;
	system->freeBlocks = block;
	system->usedMemory -= block->size;
}

void
memory_system_print_stats(const MemorySystem *system)
{
	log_info("Memory usage: %llu/%llu bytes used.", system->usedMemory,
			system->poolSize);
	log_info("Total allocations: %u", system->allocationCount);
}
