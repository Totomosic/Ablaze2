#include "Texture2D.h"
#include "Resources\Resource.h"
#include "TextureManager.h"

namespace Ablaze
{

	const Texture2D* Texture2D::s_CurrentlyBound = nullptr;

	Texture2D::Texture2D(const String& filepath, MipmapMode mm) : Texture(filepath, TextureTarget::Texture2D)
	{
		m_Format = ImageFormat::Rgba;
		int temp = 0;

		byte* imageData = ImageLoader::Load(filepath, &m_Width, &m_Height, &temp);
		Populate(imageData);
		ImageLoader::FreeData(imageData);

		if (mm == MipmapMode::Enabled)
		{
			GenerateMipmaps();
			SetMinFilter(MinFilter::Linear);
		}
	}

	Texture2D::Texture2D(uint width, uint height, ImageFormat format, MipmapMode mm) : Texture(width, height, TextureTarget::Texture2D, format)
	{
	
	}

	Texture2D::~Texture2D()
	{
		Texture::~Texture();
	}

	byte* Texture2D::GetImage(int mipmap) const
	{
		int mipWidth = m_Width / (int)pow(2, mipmap);
		int mipHeight = m_Height / (int)pow(2, mipmap);
		byte* data = new byte[mipWidth * mipHeight * 4];
		Bind();
		glGetTexImage((GLenum)m_Target, mipmap, GL_RGBA, GL_UNSIGNED_BYTE, data);
		Unbind();
		return data;
	}

	Color Texture2D::GetPixel(int x, int y) const
	{
		byte* data = GetImage();
		byte* ref = data;
		byte* color = new byte[4];
		data += (x + m_Width * y) * 4; // Assumes row-major storage
		memcpy(color, data, 4 * sizeof(byte));
		delete[] ref;
		Color c(color[0], color[1], color[2], color[3]);
		delete[] color;
		return c;
	}

	byte* Texture2D::GetRegion(int x, int y, int width, int height, int mipmap) const
	{
		int mipX = x / (int)pow(2, mipmap);
		int mipY = y / (int)pow(2, mipmap);
		int mipWidth = width / (int)pow(2, mipmap);
		int mipHeight = height / (int)pow(2, mipmap);

		byte* data = GetImage(mipmap);
		void* dataRef = data;
		byte* image = new byte[mipWidth * mipHeight * 4];
		byte* imageRef = image;

		for (int i = mipY; i < mipY + mipHeight; i++)
		{
			data += mipX * 4;
			memcpy(image, data, mipWidth * 4 * sizeof(byte));
			data -= mipX * 4;
			data += m_Width / (int)pow(2, mipmap) * 4;
			image += mipWidth * 4;
		}
		delete[] dataRef;
		return imageRef;
	}

	int Texture2D::GetMipmapCount() const
	{
		int count = 1;
		int max = max(m_Width, m_Height);
		while (max > 1)
		{
			max /= 2;
			count += 1;
		}
		return count;
	}

	void Texture2D::Bind() const
	{
		if (s_CurrentlyBound != this)
		{
			TextureManager::Instance().Bind(this);
			s_CurrentlyBound = this;
		}
	}
	
	void Texture2D::Unbind() const
	{
		// Does nothing
	}

	void Texture2D::GenerateMipmaps()
	{
		Texture::GenerateMipmaps();
		SetMinFilter(m_MinFilter);
	}

	void Texture2D::SetMinFilter(MinFilter filter) const
	{
		Bind();
		if (m_Mipmap == MipmapMode::Enabled)
		{
			if (filter == MinFilter::Linear)
			{
				glTexParameteri((GLenum)m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			}
			else if (filter == MinFilter::Nearest)
			{
				glTexParameteri((GLenum)m_Target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			}
		}
		else
		{
			glTexParameteri((GLenum)m_Target, GL_TEXTURE_MIN_FILTER, (GLenum)filter);
		}
		Unbind();
		m_MinFilter = filter;
	}

	void Texture2D::SetMagFilter(MagFilter filter) const
	{
		glTexParameteri((GLenum)m_Target, GL_TEXTURE_MAG_FILTER, (GLenum)filter);
		m_MagFilter = filter;
	}

	void Texture2D::SetWrapMode(WrapMode mode) const
	{
		glTexParameteri((GLenum)m_Target, GL_TEXTURE_WRAP_S, (GLenum)mode);
		glTexParameteri((GLenum)m_Target, GL_TEXTURE_WRAP_T, (GLenum)mode);
		glTexParameteri((GLenum)m_Target, GL_TEXTURE_WRAP_R, (GLenum)mode);
		m_WrapMode = mode;
	}

	void Texture2D::SetPixel(int x, int y, const Color& color, bool applyToMipmaps) const
	{
		byte* c = color.ToByte();
		Bind();
		glTexSubImage2D((GLenum)m_Target, 0, x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, c);
		if (applyToMipmaps)
		{
			int max = max(m_Width, m_Height);
			int level = 2;
			int mip = 1;
			while (max > 1)
			{
				glTexSubImage2D((GLenum)m_Target, mip, x / level, y / level, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, c);
				max /= 2;
				level *= 2;
				mip++;
			}
		}
		Unbind();
		delete[] c;
	}

	void Texture2D::SetRegion(int x, int y, int width, int height, const Color& color, bool applyToMipmaps) const
	{
		int total = width * height;
		byte* data = new byte[total * 4];
		void* d = data;
		byte* c = color.ToByte();
		for (int i = 0; i < total; i += 1)
		{
			memcpy(data, c, 4 * sizeof(byte));
			data += 4;
		}
		Bind();
		glTexSubImage2D((GLenum)m_Target, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, d);
		if (applyToMipmaps)
		{
			int max = max(m_Width, m_Height);
			int mip = 1;
			while (max > 1)
			{
				SetRegion(x, y, width, height, mip, data);
				max /= 2;
				mip++;
			}
		}		
		Unbind();
		delete[] d;
		delete[] c;
	}

	void Texture2D::SetRegion(int xOffset, int yOffset, int width, int height, int mipmap, const byte* image) const
	{
		Bind();
		glTexSubImage2D((GLenum)m_Target, mipmap, xOffset / (int)pow(2, mipmap), yOffset / (int)pow(2, mipmap), width / (int)pow(2, mipmap), height / (int)pow(2, mipmap), GL_RGBA, GL_UNSIGNED_BYTE, image);
		Unbind();
	}

	void Texture2D::SetRegion(int dstXOffset, int dstYOffset, int dstWidth, int dstHeight, const Resource<Texture2D>& src, int srcXOffset, int srcYOffset, bool applyToMipmaps) const
	{
		if (applyToMipmaps)
		{
			for (int i = 0; i < GetMipmapCount(); i++)
			{
				byte* data = src->GetRegion(srcXOffset, srcYOffset, dstWidth, dstHeight, i);
				SetRegion(dstXOffset, dstYOffset, dstWidth, dstHeight, i, data);
				delete[] data;
			}
		}
		else
		{
			byte* data = src->GetRegion(srcXOffset, srcYOffset, dstWidth, dstHeight, 0);
			SetRegion(dstXOffset, dstYOffset, dstWidth, dstHeight, 0, data);
			delete[] data;
		}
	}

	void Texture2D::Reload()
	{
	
	}

	String Texture2D::ToString() const
	{
		return "Texture2D";
	}

	void Texture2D::Populate(byte* pixelData)
	{
		if (m_Format == ImageFormat::Rgba)
		{
			Bind();
			SetMinFilter(MinFilter::Linear);
			SetMagFilter(MagFilter::Linear);
			glTexImage2D((GLenum)m_Target, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
			Unbind();
		}
	}

}