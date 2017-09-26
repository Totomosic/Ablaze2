#include "Texture.h"

namespace Ablaze
{

	Texture::Texture(const String& filepath, TextureTarget target) : Asset(filepath), GLObject(),
		m_Target(target), m_Mipmap(MipmapMode::Disabled), m_BindPort(-1)
	{
		Create();
	}

	Texture::Texture(uint width, uint height, TextureTarget target, ImageFormat format) : Asset(), GLObject(),
		m_Width(width), m_Height(height), m_Target(target), m_Format(format), m_Mipmap(MipmapMode::Disabled), m_BindPort(-1)
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

	ImageFormat Texture::GetFormat() const
	{
		return m_Format;
	}

	TextureTarget Texture::GetTarget() const
	{
		return m_Target;
	}

	int Texture::GetBindPort() const
	{
		return m_BindPort;
	}

	void Texture::GenerateMipmapMode()
	{
		m_Mipmap = MipmapMode::Enabled;
		Bind();
		glGenerateMipmap((GLenum)m_Target);
	}

	void Texture::Create()
	{
		glGenTextures(1, &m_Id);
	}

	void Texture::SetBindPort(int port)
	{
		m_BindPort = port;
	}

}