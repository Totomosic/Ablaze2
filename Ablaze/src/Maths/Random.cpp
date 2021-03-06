#include "Random.h"

namespace Ablaze
{

	std::minstd_rand Random::m_Gen = std::minstd_rand();


	void Random::Initialise()
	{
		m_Gen.seed((int)std::time(nullptr));
	}

	void Random::SetSeed(int64 seed)
	{
		m_Gen.seed(seed);
	}

	int Random::NextInt(int low, int high)
	{
		std::uniform_int_distribution<int> dist(low, high);
		return dist(m_Gen);
	}

	float Random::NextFloat(float low, float high)
	{
		std::uniform_real_distribution<float> dist(low, high);
		return dist(m_Gen);
	}

	float Random::NextFloat()
	{
		return NextFloat(0.0f, 1.0f);
	}

}