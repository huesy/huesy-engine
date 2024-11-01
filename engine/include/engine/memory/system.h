#ifndef MEMORY_SYSTEM_H
#define MEMORY_SYSTEM_H

#include "engine/defines.h"
#include "types.h"

typedef struct MemorySystem {
	void *state;
	u64 totalSize;
	u64 usedSize;
	MemoryAllocator allocator;
} MemorySystem;

typedef struct MemorySystemConfig {
	MemoryAllocator allocator;
} MemorySystemConfig;

MemorySystem *memory_system_create(const MemorySystemConfig *config);

#endif // MEMORY_SYSTEM_H
