#include "Plateaufunction.h"

namespace Ablaze
{

	Plateaufunction::Plateaufunction(float height) : Heightfunction(),
		m_Height(height)
	{
	
	}

	float* Plateaufunction::operator()(int x, int z, int width, int depth)
	{
		float* data = new float[width * depth];
		std::fill(data, data + width * depth, m_Height);
		return data;
	}

}