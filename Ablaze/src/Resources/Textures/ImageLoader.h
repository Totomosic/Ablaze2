#pragma once
#include "Common.h"

namespace Ablaze
{

	class AB_API ImageLoader
	{
	public:
		static byte* Load(const String& filename, uint* width, uint* height, int* components, bool flipImage = true);
		static void FreeData(byte* imageData);

	};

}