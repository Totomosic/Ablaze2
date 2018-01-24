#include "Texture.h"

namespace Ablaze
{

	Texture::Texture(TextureTarget target) : Asset(), GLObject(),
		m_Target(target), m_Mipmap(MipmapMode::Disabled)
	{
		Create();
	}

	Texture::Texture(uint width, uint height, TextureTarget target) : Asset(), GLObject(),
		m_Width(width), m_Height(height), m_Target(target), m_Mipmap(MipmapMode::Disabled)
	{
		Create();
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_Id);
	}

	uint Texture::GetWidth() const
	{
		return m_Width;
	}

	uint Texture::GetHeight() const
	{
		return m_Height;
	}

	float Texture::GetAspect() const
	{
		return (float)GetWidth() / GetHeight();
	}

	TextureTarget Texture::GetTarget() const
	{
		return m_Target;
	}

	void Texture::GenerateMipmaps()
	{
		m_Mipmap = MipmapMode::Enabled;
		Bind(0);
		GL_CALL(glGenerateMipmap((GLenum)m_Target));
	}

	void Texture::Create()
	{
		GL_CALL(glGenTextures(1, &m_Id));
	}

}