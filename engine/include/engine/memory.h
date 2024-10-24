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
	u64 poolSize; /**< The size of the memory pool. */
} MemorySystemConfig;

typedef struct MemoryBlock {
	struct MemoryBlock *next; /**< The next memory block. */
	u64 size;				  /**< The size of the memory block. */
	u8 data[];				  /**< The data of the memory block. */
} MemoryBlock;

typedef struct MemorySystem {
	u64 poolSize;			 /**< The size of the memory pool. */
	void *pool;				 /**< The memory pool. */
	u64 usedMemory;			 /**< The amount of memory used. */
	u32 allocationCount;	 /**< The number of allocation operations. */
	MemoryBlock *freeBlocks; /**< The free list of memory blocks. */
} MemorySystem;

EngineResult memory_system_init(struct Application *app,
		const MemorySystemConfig *config);
void memory_system_shutdown(struct Application *app);

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

/**
 * @brief Copies memory from one location to another.
 *
 * @param system A pointer to the memory system.
 * @param dest The destination pointer.
 * @param src The source pointer.
 * @param size The size of the memory to copy.
 * @return b8 True if the copy was successful, false otherwise.
 */
ENGINE_API b8 memory_system_copy(MemorySystem *system,
		void *dest,
		const void *src,
		u64 size);

/**
 * @brief Reallocates memory on the heap.
 *
 * @param system A pointer to the memory system.
 */
void memory_system_print_stats(const MemorySystem *system);

#endif // ENGINE_MEMORY_H
