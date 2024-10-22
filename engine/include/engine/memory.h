/**
 * @file memory.h
 * @brief Memory management for the engine.
 * @author Andrew Hughes
 * @version 0.1
 * @date 2024-10-21
 * @copyright Huesy Engine is Copyright (c) 2024 Andrew Hughes
 */

#ifndef ENGINE_MEMORY_H
#define ENGINE_MEMORY_H

#include "engine/defines.h"

typedef struct MemorySystemConfig {
	/** @brief The size of the memory pool. */
	u64 poolSize;
} MemorySystemConfig;

typedef struct MemorySystem {
	/** @brief The size of the memory pool. */
	u64 poolSize;
	/** @brief The memory pool. */
	void *pool;
} MemorySystem;

EngineResult memory_system_init(MemorySystem *system,
		const MemorySystemConfig *config);
void memory_system_shutdown(MemorySystem *system);

/**
 * @brief Allocates memory on the heap.
 *
 * @param system A pointer to the memory system.
 * @param size The size of the memory to allocate.
 * @return void* A pointer to the allocated memory.
 */
ENGINE_API void *memory_system_allocate(MemorySystem *system, u64 size);

/**
 * @brief Frees memory on the heap.
 *
 * @param system A pointer to the memory system.
 * @param ptr The pointer to the memory to free.
 */
ENGINE_API void memory_system_free(MemorySystem *system, void *ptr);

#endif // ENGINE_MEMORY_H
