#include "engine/memory.h"
#include "engine/logging.h"
#include "engine/platform.h"
#include <stdio.h>

EngineResult
memory_system_init(MemorySystem **system, const MemorySystemConfig *config)
{
	// Allocate memory for the memory system itself.
	*system = platform_memory_allocate(sizeof(MemorySystem));
	if (*system == NULL) {
		log_error("Failed to allocate memory for memory system.");
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	// Initialize the memory system.
	MemorySystem *memorySystem = *system;
	memorySystem->poolSize = config->poolSize;
	memorySystem->pool = platform_memory_allocate(memorySystem->poolSize);
	if (memorySystem->pool == NULL) {
		log_error("Failed to allocate memory pool.");
		platform_memory_free(*system);
		return ENGINE_ERROR_ALLOCATION_FAILED;
	}

	memorySystem->usedMemory = 0;
	memorySystem->allocationCount = 0;
	memorySystem->freeBlocks = NULL; // Initially there are no free blocks.
	log_info("Memory system initialized with pool size %llu bytes.",
			memorySystem->poolSize);

	return ENGINE_SUCCESS;
}

void
memory_system_shutdown(MemorySystem *system)
{
	// Store the allocation count before we free the pool so we can log it.
	u32 allocationCount = system->allocationCount;

	platform_memory_free(system->pool);
	platform_memory_free(system);

	log_info("Memory system shut down. Total allocations: %u", allocationCount);
}

void *
memory_system_allocate(MemorySystem *system, u64 size)
{
	// Calculate total size needed including the block header.
	u64 totalSize = sizeof(MemoryBlock) + size;

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
			// We need to track this memory as used since we're reusing it
			system->usedMemory += totalSize;
			system->allocationCount++;
			return block->data;
		}
		prev = block;
		block = block->next;
	}

	// If no suitable free block is found, allocate new memory.
	if (system->usedMemory + totalSize > system->poolSize) {
		log_error(
				"Memory system out of memory. Used %llu, Requested: %llu, "
				"Pool: %llu",
				system->usedMemory, totalSize, system->poolSize);
		return NULL;
	}

	// Create new block at the current position.
	MemoryBlock *newBlock =
			(MemoryBlock *)((u8 *)system->pool + system->usedMemory);
	newBlock->size = size;
	newBlock->next = NULL;

	system->usedMemory += totalSize;
	system->allocationCount++;

	return newBlock->data;
}

void
memory_system_free(MemorySystem *system, void *ptr)
{
	if (ptr == NULL) {
		log_error("Attempted to free NULL pointer.");
		return;
	}

	MemoryBlock *block = (MemoryBlock *)((u8 *)ptr - sizeof(MemoryBlock));

	// Validate the pointer is within our pool.
	if ((u8 *)block < (u8 *)system->pool ||
			(u8 *)block >= ((u8 *)system->pool + system->poolSize)) {
		log_error("Invalid pointer freed!");
		return;
	}

	// Add the block to the free list.
	block->next = system->freeBlocks;
	system->freeBlocks = block;
	system->usedMemory -= (sizeof(MemoryBlock) + block->size);
	log_debug("Freed memory. New used: %llu", system->usedMemory);
}

void
memory_system_print_stats(const MemorySystem *system)
{
	log_info("Memory usage: %llu/%llu bytes used.", system->usedMemory,
			system->poolSize);
	log_info("Total allocations: %u", system->allocationCount);
}
