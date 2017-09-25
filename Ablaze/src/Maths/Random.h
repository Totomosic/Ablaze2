#pragma once
#include "Types.h"
#include <random>
#include <ctime>

namespace Ablaze
{

	class AB_API Random
	{
	private:
		static std::minstd_rand m_Gen;

		Random() = delete;

	public:
		static void Initialise();
		static void SetSeed(int64 seed);

		static int NextInt(int low, int high);
		static float NextFloat(float low, float high);
		static float NextFloat();
	};

}