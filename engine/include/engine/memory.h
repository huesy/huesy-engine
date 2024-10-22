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

/**
 * @brief Allocates memory on the heap.
 *
 * @param size The size of the memory to allocate.
 * @return void* A pointer to the allocated memory.
 */
ENGINE_API void *memory_allocate(u64 size);

/**
 * @brief Frees memory on the heap.
 *
 * @param ptr The pointer to the memory to free.
 */
ENGINE_API void memory_free(void *ptr);

#endif // ENGINE_MEMORY_H
