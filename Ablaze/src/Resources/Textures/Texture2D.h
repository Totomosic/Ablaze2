#pragma once
#include "Common.h"
#include "Texture.h"

namespace Ablaze
{

	class Texture2D : public Texture
	{
	private:
		static const Texture2D* s_CurrentlyBound;

	private:
		Texture2D(const String& filepath, Mipmaps mm);
		Texture2D(uint width, uint height, ImageFormat format, Mipmaps mm);

	public:
		void Bind() const override;
		void Unbind() const override;

		void SetMinFilter(MinFilter filter) const override;
		void SetMagFilter(MagFilter filter) const override;
		void Reload() override;

		String ToString() const override;

		friend class ResourceManager;

	private:
		void Populate(byte* pixelData) override;

	};

}