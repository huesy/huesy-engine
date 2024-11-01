#ifndef MEMORY_TYPES_H
#define MEMORY_TYPES_H

#include "engine/defines.h"

typedef struct MemoryBlock {
	void *data;
	u64 size;
	u64 alignment;
} MemoryBlock;

typedef struct MemoryAllocator {
	void *(*allocate)(u64 size, u64 alignment);
	void (*free)(void *ptr);
	void *(*reallocate)(void *ptr, u64 newSize, u64 alignment);
} MemoryAllocator;

#endif // MEMORY_TYPES_H
