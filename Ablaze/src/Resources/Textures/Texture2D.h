#pragma once
#include "Common.h"
#include "Texture.h"

namespace Ablaze
{

	class AB_API Texture2D : public Texture
	{
	protected:
		mutable MinFilter m_MinFilter;
		mutable MagFilter m_MagFilter;
		mutable WrapMode m_WrapMode;

	public:
		Color* Pixels;

	public:
		Texture2D(const Filepath& filepath, MipmapMode mm = MipmapMode::Enabled);
		Texture2D(uint width, uint height, MipmapMode mm = MipmapMode::Enabled);

	public:
		byte* GetImage(int mipmap = 0) const;
		Color GetPixel(int x, int y) const;
		byte* GetRegion(int x, int y, int width, int height, int mipmap = 0) const;
		int GetMipmapCount() const;

		void Bind() const override;
		void Unbind() const override;
		void Bind(int bindPort) const override;

		void LoadPixels();
		void UpdatePixels();

		void GenerateMipmaps() override;

		void SetMinFilter(MinFilter filter) const override;
		void SetMagFilter(MagFilter filter) const override;
		void SetWrapMode(WrapMode mode) const override;
		void SetPixel(int x, int y, const Color& color, bool applyToMipmaps = true) const;
		void SetRegion(int xOffset, int yOffset, int width, int height, const Color& color, bool applyToMipmaps = true) const; // Specified from lower left corner
		void SetRegion(int xOffset, int yOffset, int width, int height, int mipmap, const byte* image) const;
		void SetRegion(int dstXOffset, int dstYOffset, int dstWidth, int dstHeight, Texture2D* src, int srcXOffset, int srcYOffset, bool applyToMipmaps = true) const;
		void Reload() override;

		String ToString() const override;

		friend class ResourceManager;

	private:
		void Populate(byte* pixelData) override;

		template<typename T>
		T* Compress(T* pixelData, int width, int height, int compressions = 1, MinFilter filter = MinFilter::Nearest) const
		{
			if (filter == MinFilter::Nearest)
			{
				return CompressNearest<T>(pixelData, width, height, compressions);
			}
			return CompressLinear<T>(pixelData, width, height, compressions);
		}

		template<typename T>
		T* CompressNearest(T* pixelData, int width, int height, int compressions) const
		{
			int indexMultiplier = pow(2, compressions);
			int newWidth = width / indexMultiplier;
			int newHeight = height / indexMultiplier;
			T* newData = new T[newWidth * newHeight * 4];
			for (int x = 0; x < newWidth; x++)
			{
				for (int y = 0; y < newHeight; y++)
				{
					int index = x + y * newWidth;
					int secondIndex = x * indexMultiplier + y * indexMultiplier * newWidth;
					newData[index * 4 + 0] = pixelData[secondIndex * 4 + 0];
					newData[index * 4 + 1] = pixelData[secondIndex * 4 + 1];
					newData[index * 4 + 2] = pixelData[secondIndex * 4 + 2];
					newData[index * 4 + 3] = pixelData[secondIndex * 4 + 3];
				}
			}
			return newData;
		}

		template<typename T>
		T* CompressLinear(T* pixelData, int width, int height, int compressions) const
		{
			return pixelData;
		}

	};

}