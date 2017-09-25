#pragma once
#include "Common.h"

namespace Ablaze
{
	namespace Internal
	{

		void* Allocate(size_t size);
		void Free(void* ptr);

	}
}