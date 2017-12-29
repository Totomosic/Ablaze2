#include "Memory.h"

#if AB_USE_CUSTOM_ALLOCATOR

void* operator new(size_t size)
{
	return Ablaze::Internal::Allocate(size);
}

void* operator new[](size_t size)
{
	return Ablaze::Internal::Allocate(size);
}

void operator delete(void* block)
{
	Ablaze::Internal::Free(block);
	block = nullptr;
}

void operator delete[](void* block)
{
	Ablaze::Internal::Free(block);
	block = nullptr;
}

#endif