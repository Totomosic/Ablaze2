#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"

namespace Ablaze
{

	int Bit(int bit);
	bool IsBitSet(int bitfield, int bit);

	float Map(float value, float min, float max, float newMin, float newMax);
	float Clamp(float value, float min, float max);

	float ToRadians(float degrees);
	float ToDegrees(float radians);

	std::vector<String> SplitString(const String& str, const String& delimeters);
	String CleanString(const String& str);

}