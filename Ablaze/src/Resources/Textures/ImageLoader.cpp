#include "ImageLoader.h"
#include "stb_image.h"

namespace Ablaze
{

	byte* ImageLoader::Load(const String& filename, uint* width, uint* height, int* components)
	{
		int w = 0;
		int h = 0;
		stbi_set_flip_vertically_on_load(true);
		byte* image = stbi_load(filename.c_str(), &w, &h, components, STBI_rgb_alpha);
		*width = (uint)(abs(w));
		*height = (uint)(abs(h));
		if (image == nullptr)
		{
			AB_ERROR("Failed to load image: " + filename);
		}
		return image;
	}

	void ImageLoader::FreeData(byte* imageData)
	{
		stbi_image_free(imageData);
	}

}