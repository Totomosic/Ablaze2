#include "HeightmapFunction.h"

namespace Ablaze
{

	HeightmapFunction::HeightmapFunction(const String& heightmap, float minHeight, float maxHeight) : Heightfunction(),
		m_MinHeight(minHeight), m_MaxHeight(maxHeight)
	{
		int comp;
		m_Image = LoadImageFile(heightmap, false);
	}

	HeightmapFunction::~HeightmapFunction()
	{
		FreeImageData(m_Image);
	}

	float* HeightmapFunction::operator()(int x, int z, int width, int depth)
	{
		float* data = new float[width * depth];
		int index = 0;
		for (int i = z; i < z + depth; i++)
		{
			for (int j = x; j < x + width; j++)
			{
				float brightness = (m_Image.Pixels[(j + i * m_Image.Width) * 4 + 0] + m_Image.Pixels[(j + i * m_Image.Width) * 4 + 1] + m_Image.Pixels[(j + i * m_Image.Width) * 4 + 2]) / (3 * 255.0f);
				float height = Map(brightness, 0, 1, m_MinHeight, m_MaxHeight);
				data[index] = height;
				index++;
			}
		}
		return data;
	}

}