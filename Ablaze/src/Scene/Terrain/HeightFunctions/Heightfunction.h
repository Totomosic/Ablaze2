#pragma once
#include "Common.h"

namespace Ablaze
{

	struct AB_API Heightfunction
	{
	public:		
		virtual ~Heightfunction() {}

		virtual float* operator()(int xOffset, int zOffset, int xVertices, int zVertices) = 0;

	};

}