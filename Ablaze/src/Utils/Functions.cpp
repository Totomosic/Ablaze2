#include "Functions.h"
#include "stb_image.h"

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
		std::stringstream ss;
		for (auto chr : str)
		{
			if (chr != '\n' && chr != ' ' && chr != '\r' && chr != '\t')
			{
				ss << chr;
			}
		}
		String s = ss.str();
		return s;
	}

	byte* LoadImageFile(const String& filename, uint* outWidth, uint* outHeight, int* outCompCount, int desiredCompCount, bool flipImage)
	{
		int width;
		int height;
		int comp;
		stbi_set_flip_vertically_on_load(flipImage);
		byte* data = stbi_load(filename.c_str(), &width, &height, &comp, desiredCompCount);
		if (outWidth) *outWidth = (uint)width;
		if (outHeight) *outHeight = (uint)height;
		if (outCompCount) *outCompCount = comp;
		return data;
	}

	byte* LoadImageFile(const String& filename, uint* outWidth, uint* outHeight, int desiredCompCount, bool flipImage)
	{
		return LoadImageFile(filename, outWidth, outHeight, nullptr, desiredCompCount, flipImage);
	}

	byte* LoadImageFile(const String& filename, uint* outWidth, uint* outHeight, int* outCompCount, bool flipImage)
	{
		return LoadImageFile(filename, outWidth, outHeight, outCompCount, 4, flipImage);
	}

	byte* LoadImageFile(const String& filename, uint* outWidth, uint* outHeight, bool flipImage)
	{
		return LoadImageFile(filename, outWidth, outHeight, nullptr, flipImage);
	}

	void FreeImageData(byte* imageData)
	{
		stbi_image_free(imageData);
	}

}