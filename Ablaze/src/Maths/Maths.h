#pragma once
#include "Types.h"

namespace Ablaze
{
	namespace Maths
	{
		const double PI = M_PI;

		float Clamp(float value, float min, float max);
		float Map(float value, float min, float max, float newMin, float newMax);

		float ToRadians(float degrees);
		float ToDegrees(float radians);

	}
}