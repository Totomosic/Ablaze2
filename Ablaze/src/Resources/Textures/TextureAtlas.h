#pragma once
#include "Texture2D.h"

namespace Ablaze
{

	// TEXTURE MATRIX IN SHADER?
	// MAKE ABILITY TO CHANGE TEXTURE ON SIDES OF SHAPES

	struct AB_API TextureBounds
	{
	public:
		float Left;
		float Bottom;
		float Right;
		float Top;

	};

	class AB_API TextureAtlas : public Texture2D
	{
	private:

	public:
		TextureAtlas(int width, int height);
		TextureAtlas(const Filepath& filepath, int rows, int columns);

		int TextureCount() const;
		TextureBounds GetTexture(int index) const;

		int AddTexture(Texture2D* image);
		int AddTexture(Image image);


	};

}