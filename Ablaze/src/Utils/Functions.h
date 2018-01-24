#pragma once
#include "Maths\__Maths__.h"
#include "Object.h"
#include "structs\Image.h"

namespace Ablaze
{

	class Filepath;

	int Bit(int bit);
	bool IsBitSet(int bitfield, int bit);

	float Map(float value, float min, float max, float newMin, float newMax);
	float Clamp(float value, float min, float max);

	float ToRadians(float degrees);
	float ToDegrees(float radians);

	std::vector<String> SplitString(const String& str, const String& delimeter);
	std::vector<String> SplitStringOnce(const String& str, const String& delimeter);
	String CleanString(const String& str);
	String CleanString(const String& str, const std::vector<char>& remove);

	// Image loading
	Image LoadImageFile(const Filepath& imageFile, int desiredComponents, bool flipImage = true);
	Image LoadImageFile(const Filepath& imageFile, bool flipImage = true);
	void FreeImageData(Image& imageData);

}