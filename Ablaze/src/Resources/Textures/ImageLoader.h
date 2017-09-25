#pragma once
#include "Common.h"

namespace Ablaze
{

	class ImageLoader
	{
	public:
		static byte* Load(const String& filename, uint* width, uint* height, int* components);
		static void FreeData(byte* imageData);

	};

}