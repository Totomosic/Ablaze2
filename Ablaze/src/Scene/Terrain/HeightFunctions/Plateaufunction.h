#pragma once
#include "Heightfunction.h"

namespace Ablaze
{

	struct AB_API Plateaufunction : public Heightfunction
	{
	private:
		float m_Height;

	public:
		Plateaufunction(float height);

		float* operator()(int x, int z, int width, int depth) override;

	};

}