#pragma once
#include "Allocator.h"

#define AB_USE_CUSTOM_ALLOCATOR 1

#if AB_USE_CUSTOM_ALLOCATOR

inline void* operator new(size_t size)
{
	return Ablaze::Internal::Allocate(size);
}

inline void* operator new[](size_t size)
{
	return Ablaze::Internal::Allocate(size);
}

inline void operator delete(void* block)
{
	Ablaze::Internal::Free(block);
	block = nullptr;
}

inline void operator delete[](void* block)
{
	Ablaze::Internal::Free(block);
	block = nullptr;
}

#endif