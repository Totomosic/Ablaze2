#pragma once
#include "Common.h"
#include "Resources\Asset.h"

namespace Ablaze
{

	enum class TextureTarget : GLenum
	{
		Texture1D = GL_TEXTURE_1D,
		Texture2D = GL_TEXTURE_2D,
		Texture3D = GL_TEXTURE_3D,
		TextureCube = GL_TEXTURE_CUBE_MAP
	};

	enum class ImageFormat : GLenum
	{
		Rgba = GL_RGBA,
		Bgra = GL_BGRA,
		Rgb = GL_RGB,
		Bgr = GL_BGR,
		Red = GL_RED,
		Green = GL_GREEN,
		Blue = GL_BLUE,
		Alpha = GL_ALPHA
	};

	enum class MipmapMode
	{
		Enabled,
		Disabled
	};

	enum class MinFilter : GLenum
	{
		Linear = GL_LINEAR,
		Nearest = GL_NEAREST
	};

	enum class MagFilter : GLenum
	{
		Linear = GL_LINEAR,
		Nearest = GL_NEAREST
	};

	enum class WrapMode : GLenum
	{
		Repeat = GL_REPEAT,
		Clamp = GL_CLAMP
	};

	class AB_API Texture : public Asset, public GLObject
	{
	protected:
		uint m_Width;
		uint m_Height;
		TextureTarget m_Target;
		MipmapMode m_Mipmap;

	public:
		Texture(TextureTarget target);
		Texture(uint width, uint height, TextureTarget target);
		~Texture() override;

	public:
		uint GetWidth() const;
		uint GetHeight() const;
		float GetAspect() const;
		TextureTarget GetTarget() const;

		virtual void Bind(int bindPort) const = 0;

		virtual void GenerateMipmaps();
		virtual void SetMinFilter(MinFilter filter) const = 0;
		virtual void SetMagFilter(MagFilter filter) const = 0;
		virtual void SetWrapMode(WrapMode mode) const = 0;

		friend class ResourceManager;

	private:
		void Create();
		virtual void Populate(byte* pixelData) = 0;

	};

}