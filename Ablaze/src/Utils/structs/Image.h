#pragma once
#include "Types.h"

namespace Ablaze
{

	struct AB_API Image
	{
	public:
		byte* Pixels;
		int Width;
		int Height;
		int Components;

	};

}