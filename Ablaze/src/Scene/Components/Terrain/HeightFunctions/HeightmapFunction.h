#pragma once
#include "Heightfunction.h"

namespace Ablaze
{

	struct AB_API HeightmapFunction : public Heightfunction
	{
	private:
		Image m_Image;

		float m_MinHeight;
		float m_MaxHeight;

	public:
		HeightmapFunction(const String& heightmap, float minHeight, float maxHeight);
		~HeightmapFunction();

		float* operator()(int x, int z, int width, int depth) override;

	};

}