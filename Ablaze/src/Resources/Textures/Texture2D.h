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
		Texture2D(const String& filepath, MipmapMode mm);
		Texture2D(uint width, uint height, ImageFormat format, MipmapMode mm);

	public:
		byte* GetImage(int mipmap = 0) const;
		Color GetPixel(int x, int y) const;
		byte* GetRegion(int x, int y, int width, int height, int mipmap = 0) const;
		int GetMipmapCount() const;

		void Bind() const override;
		void Unbind() const override;

		void GenerateMipmaps() override;

		void SetMinFilter(MinFilter filter) const override;
		void SetMagFilter(MagFilter filter) const override;
		void SetWrapMode(WrapMode mode) const override;
		void SetPixel(int x, int y, const Color& color, bool applyToMipmaps = true) const;
		void SetRegion(int xOffset, int yOffset, int width, int height, const Color& color, bool applyToMipmaps = true) const; // Specified from lower left corner
		void SetRegion(int xOffset, int yOffset, int width, int height, int mipmap, const byte* image) const;
		void SetRegion(int dstXOffset, int dstYOffset, int dstWidth, int dstHeight, const std::shared_ptr<Texture2D>& src, int srcXOffset, int srcYOffset, bool applyToMipmaps = true) const;
		void Reload() override;

		String ToString() const override;

		friend class ResourceManager;
		template<typename> friend class Resource;

	private:
		void Populate(byte* pixelData) override;

	};

}