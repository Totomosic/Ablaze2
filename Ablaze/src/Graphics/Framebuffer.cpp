#include "Framebuffer.h"
#include "Resources\ResourceManager.h"
#include "Graphics\Rendering\Graphics.h"

namespace Ablaze
{

	Framebuffer::Framebuffer(int width, int height)
		: m_Viewport(Viewport(width, height)), m_ClearColor(Color::Black())
	{
	
	}

	Framebuffer::Framebuffer(int width, int height, bool createOnLoad, const Color& clearColor)
		: m_Viewport(Viewport(width, height)), m_ClearColor(clearColor)
	{
		GL_CALL(glGenFramebuffers(1, &m_Id));
		if (createOnLoad)
		{
			CreateColorTextureAttachment();
			CreateDepthTextureAttachment();
		}
	}

	Framebuffer::~Framebuffer()
	{
		if (m_Id != 0) // Check for window framebuffer
		{
			GL_CALL(glDeleteFramebuffers(1, &m_Id));
		}
	}

	const Color& Framebuffer::GetClearColor() const
	{
		return m_ClearColor;
	}

	int Framebuffer::Width() const
	{
		return m_Viewport.GetWidth();
	}

	int Framebuffer::Height() const
	{
		return m_Viewport.GetHeight();
	}

	float Framebuffer::GetAspect() const
	{
		return m_Viewport.GetAspect();
	}

	const Viewport& Framebuffer::GetViewport() const
	{
		return m_Viewport;
	}

	Viewport& Framebuffer::GetViewport()
	{
		return m_Viewport;
	}

	void Framebuffer::Clear(ClearBuffer buffer) const
	{
		Bind();
		GL_CALL(glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a));
		GL_CALL(glClear((GLbitfield)buffer));
	}

	void Framebuffer::Bind() const
	{
		m_Viewport.Bind();
		GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_Id));
	}

	void Framebuffer::Unbind() const
	{
		// Does nothing
	}

	void Framebuffer::SetClearColor(const Color& clearColor)
	{
		m_ClearColor = clearColor;
	}

	Texture2D* Framebuffer::GetTexture(ColorBuffer buffer) const
	{
		return m_Textures.at(buffer);
	}

	void Framebuffer::CopyToScreen(ClearBuffer buffer, Filter filter, ColorBuffer readBuffer) const
	{
		GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
		GL_CALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Id));
		GL_CALL(glReadBuffer((GLenum)readBuffer));
		GL_CALL(glDrawBuffer(GL_FRONT_AND_BACK));
		GL_CALL(glBlitFramebuffer(0, 0, Width(), Height(), 0, 0, Graphics::CurrentContext().Width(), Graphics::CurrentContext().Height(), (GLbitfield)buffer, (GLenum)filter));
		GL_CALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
		GL_CALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
	}

	void Framebuffer::CreateColorTextureAttachment(Texture2D* texture, ColorBuffer buffer)
	{
		Bind();
		texture->Bind();
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
		texture->SetMagFilter(MagFilter::Linear);
		texture->SetMinFilter(MinFilter::Linear);
		texture->SetWrapMode(WrapMode::Clamp);
		GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)buffer, GL_TEXTURE_2D, texture->GetID(), 0));
		GL_CALL(glDrawBuffer((GLenum)buffer));
		m_Textures[buffer] = texture;
	}

	void Framebuffer::CreateColorTextureAttachment(ColorBuffer buffer)
	{
		CreateColorTextureAttachment(new Texture2D(Width(), Height(), MipmapMode::Disabled), buffer);
	}

	void Framebuffer::CreateDepthTextureAttachment(Texture2D* texture)
	{
		Bind();
		texture->Bind();
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, texture->GetWidth(), texture->GetHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr));
		texture->SetMagFilter(MagFilter::Linear);
		texture->SetMinFilter(MinFilter::Linear);
		texture->SetWrapMode(WrapMode::Clamp);
		GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetID(), 0));
		m_Textures[ColorBuffer::Depth] = texture;
	}

	void Framebuffer::CreateDepthTextureAttachment()
	{
		CreateDepthTextureAttachment(new Texture2D(Width(), Height(), MipmapMode::Disabled));
	}

	String Framebuffer::ToString() const
	{
		return "Framebuffer";
	}

	Framebuffer* Framebuffer::WindowFramebuffer(int width, int height)
	{
		return new Framebuffer(width, height);
	}

}