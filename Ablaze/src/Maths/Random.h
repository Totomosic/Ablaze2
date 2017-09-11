#pragma once
#include "Types.h"
#include <random>
#include <ctime>

namespace Ablaze
{

	class AB_API Random
	{
	private:
		static std::minstd_rand gen;

		Random() = delete;

	public:
		static void Initialise();
		static void SetSeed(long long seed);

		static int NextInt(int low, int high);
		static float NextFloat(float low, float high);
		static float NextFloat();
	};

}