#include "Allocator.h"

namespace Ablaze
{
	namespace Internal
	{

#define AB_MEMORY_ALIGNMENT 16
#define AB_ALLOC(size)	_aligned_malloc(size, AB_MEMORY_ALIGNMENT)
#define AB_FREE(block)	_aligned_free(block);

		void* Allocate(size_t size)
		{
			if (size > 1024 * 1024)
			{
				AB_WARN("Large Allocation: " + std::to_string(size / 1024) + " KB");
			}
			return AB_ALLOC(size);
		}

		void Free(void* ptr)
		{
			return AB_FREE(ptr);
		}

	}
}