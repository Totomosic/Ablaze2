#pragma once
#include "Common.h"
#include "Texture.h"

namespace Ablaze
{

	template<typename> class Resource;

	class AB_API Texture2D : public Texture
	{
	private:
		static const Texture2D* s_CurrentlyBound;

	protected:
		mutable MinFilter m_MinFilter;
		mutable MagFilter m_MagFilter;

	protected:
		Texture2D(const String& filepath, MipmapMode mm);
		Texture2D(uint width, uint height, ImageFormat format, MipmapMode mm);
		~Texture2D();

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
		void SetPixel(int x, int y, const Color& color, bool applyToMipmaps = true) const;
		void SetRegion(int xOffset, int yOffset, int width, int height, const Color& color, bool applyToMipmaps = true) const; // Specified from lower left corner
		void SetRegion(int xOffset, int yOffset, int width, int height, int mipmap, const byte* image) const;
		void SetRegion(int dstXOffset, int dstYOffset, int dstWidth, int dstHeight, const Resource<Texture2D>& src, int srcXOffset, int srcYOffset, bool applyToMipmaps = true) const;
		void Reload() override;

		String ToString() const override;

		friend class ResourceManager;

	private:
		void Populate(byte* pixelData) override;

	};

}