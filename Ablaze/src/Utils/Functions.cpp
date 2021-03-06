#include "Functions.h"
#include "stb_image.h"

#include "Utils\Filesystem\Filesystem.h"

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

	std::vector<String> SplitString(const String& string, const String& delimiter)
	{
		size_t start = 0;
		size_t end = string.find_first_of(delimiter);

		std::vector<String> result;

		while (end <= String::npos)
		{
			String token = string.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == String::npos)
				break;

			start = end + 1;
			end = string.find_first_of(delimiter, start);
		}

		return result;
	}

	std::vector<String> SplitStringOnce(const String& string, const String& delimeter)
	{
		std::vector<String> result;
		result.reserve(2);
		size_t end = string.find_first_of(delimeter);
		result.push_back(string.substr(0, end));
		result.push_back(string.substr(end + 1, string.length() - end - 1));
		return result;
	}

	String CleanString(const String& str)
	{
		return CleanString(str, { '\n', ' ', '\r', '\t' });
	}

	String CleanString(const String& str, const std::vector<char>& remove)
	{
		std::stringstream ss;
		for (auto chr : str)
		{
			if (!(std::find(remove.begin(), remove.end(), chr) != remove.end()))
			{
				ss << chr;
			}
		}
		String s = ss.str();
		return s;
	}

	Image LoadImageFile(const Filepath& filename, int desiredComponents, bool flipImage)
	{
		AB_ASSERT(filename.Exists(), "File: " + filename.Path() + " could not be found");
		Image result;
		stbi_set_flip_vertically_on_load(flipImage);
		result.Pixels = stbi_load(filename.Path().c_str(), &result.Width, &result.Height, &result.Components, desiredComponents);
		return result;
	}

	Image LoadImageFile(const Filepath& filename, bool flipImage)
	{
		return LoadImageFile(filename, 4, flipImage);
	}

	void FreeImageData(Image& imageData)
	{
		stbi_image_free(imageData.Pixels);
	}

}