#include "Random.h"

namespace Ablaze
{

	std::minstd_rand Random::gen = std::minstd_rand();


	void Random::Initialise()
	{
		gen.seed((int)std::time(nullptr));
	}

	void Random::SetSeed(long long seed)
	{
		gen.seed(seed);
	}

	int Random::NextInt(int low, int high)
	{
		std::uniform_int_distribution<int> dist(low, high);
		return dist(gen);
	}

	float Random::NextFloat(float low, float high)
	{
		std::uniform_real_distribution<float> dist(low, high);
		return dist(gen);
	}

	float Random::NextFloat()
	{
		return NextFloat(0.0f, 1.0f);
	}

}