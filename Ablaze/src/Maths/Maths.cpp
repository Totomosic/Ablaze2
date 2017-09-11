#include "Maths.h"

namespace Ablaze
{
	namespace Maths
	{

		float Clamp(float value, float min, float max)
		{
			if (value > max)
				return max;
			if (value < min)
				return min;
			return value;
		}

		float Map(float value, float min, float max, float newMin, float newMax)
		{
			return ((value - min) / (max - min)) * (newMax - newMin) + newMin;
		}

		float ToRadians(float degrees)
		{
			return degrees * ((float)PI / 180.0f);
		}

		float ToDegrees(float radians)
		{
			return radians / (float)PI * 180.0f;
		}

	}
}