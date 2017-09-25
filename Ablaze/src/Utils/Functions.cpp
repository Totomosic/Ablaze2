#include "Functions.h"

namespace Ablaze
{

	int Bit(int bit)
	{
		return 1 << bit;
	}

	bool IsBitSet(int bitfield, int bit)
	{
		return bitfield & (1 << bit);
	}

	float Map(float value, float min, float max, float newMin, float newMax)
	{
		return ((value - min) / (max - min)) * (newMax - newMin) + newMin;
	}

	float Clamp(float value, float min, float max)
	{
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}

	float ToRadians(float degrees)
	{
		return degrees * ((float)Maths::PI / 180.0f);
	}

	float ToDegrees(float radians)
	{
		return radians / (float)Maths::PI * 180.0f;
	}

}