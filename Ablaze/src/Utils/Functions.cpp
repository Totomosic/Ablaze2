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

	std::vector<String> SplitString(const String& string, const String& delimiters)
	{
		size_t start = 0;
		size_t end = string.find_first_of(delimiters);

		std::vector<String> result;

		while (end <= String::npos)
		{
			String token = string.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == String::npos)
				break;

			start = end + 1;
			end = string.find_first_of(delimiters, start);
		}

		return result;
	}

	String CleanString(const String& str)
	{
		std::stringstream ss;
		for (auto chr : str)
		{
			if (chr != '\n' && chr != ' ' && chr != '\r')
			{
				ss << chr;
			}
		}
		String s = ss.str();
		return s;
	}

}