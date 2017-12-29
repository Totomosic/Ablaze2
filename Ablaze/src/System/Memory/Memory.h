#pragma once
#include "Allocator.h"

#define AB_USE_CUSTOM_ALLOCATOR 1

#if AB_USE_CUSTOM_ALLOCATOR

void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* block);
void operator delete[](void* block);

#endif