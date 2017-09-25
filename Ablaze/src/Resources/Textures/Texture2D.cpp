#include "Texture2D.h"

namespace Ablaze
{

	const Texture2D* Texture2D::s_CurrentlyBound = nullptr;

	Texture2D::Texture2D(const String& filepath, Mipmaps mm) : Texture(filepath, TextureTarget::Texture2D)
	{
		m_Format = ImageFormat::Rgba;
		int temp = 0;

		byte* imageData = ImageLoader::Load(filepath, &m_Width, &m_Height, &temp);
		Populate(imageData);
		ImageLoader::FreeData(imageData);

		if (mm == Mipmaps::Enabled)
		{
			GenerateMipmaps();
			SetMinFilter(MinFilter::Linear);
		}
	}

	Texture2D::Texture2D(uint width, uint height, ImageFormat format, Mipmaps mm) : Texture(width, height, TextureTarget::Texture2D, format)
	{
	
	}

	void Texture2D::Bind() const
	{
		if (s_CurrentlyBound != this)
		{
			glBindTexture((GLenum)m_Target, m_Id);
			s_CurrentlyBound = this;
		}
	}
	
	void Texture2D::Unbind() const
	{
		// Does nothing
	}

	void Texture2D::SetMinFilter(MinFilter filter) const
	{
		Bind();
		if (m_Mipmap == Mipmaps::Enabled)
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
	}

	void Texture2D::SetMagFilter(MagFilter filter) const
	{
		glTexParameteri((GLenum)m_Target, GL_TEXTURE_MAG_FILTER, (GLenum)filter);
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