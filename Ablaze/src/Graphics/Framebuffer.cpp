#include "Framebuffer.h"
#include "Resources\ResourceManager.h"
#include "Graphics\Graphics.h"
#include "Resources\Resource.h"

namespace Ablaze
{

	const Framebuffer* Framebuffer::s_CurrentlyBound = nullptr;

	Framebuffer::Framebuffer(int width, int height)
		: m_Viewport(Viewport(width, height)), m_ClearColor(Color::Black())
	{
	
	}

	Framebuffer::Framebuffer(int width, int height, bool createOnLoad, const Color& clearColor)
		: m_Viewport(Viewport(width, height)), m_ClearColor(clearColor)
	{
		glGenFramebuffers(1, &m_Id);
		if (createOnLoad)
		{
			CreateColorTextureAttachment();
			CreateDepthTextureAttachment();
		}
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_Id);
	}

	const Color& Framebuffer::GetClearColor() const
	{
		return m_ClearColor;
	}

	int Framebuffer::GetWidth() const
	{
		return m_Viewport.GetWidth();
	}

	int Framebuffer::GetHeight() const
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

	void Framebuffer::Clear(ClearBuffer buffer) const
	{
		Bind();
		glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
		glClear((GLbitfield)buffer);
	}

	void Framebuffer::Bind() const
	{
		if (s_CurrentlyBound != this)
		{
			m_Viewport.Bind();
			glBindFramebuffer(GL_FRAMEBUFFER, m_Id);
			s_CurrentlyBound = this;
		}
	}

	void Framebuffer::Unbind() const
	{
		// Does nothing
	}

	void Framebuffer::SetClearColor(const Color& clearColor)
	{
		m_ClearColor = clearColor;
	}

	void Framebuffer::SetWidth(int width)
	{
		m_Viewport.SetWidth(width);
	}

	void Framebuffer::SetHeight(int height)
	{
		m_Viewport.SetHeight(height);
	}

	const Resource<Texture2D>& Framebuffer::GetTexture(ColorBuffer buffer) const
	{
		return m_Textures.at(buffer);
	}

	Resource<Texture2D>& Framebuffer::GetTexture(ColorBuffer buffer)
	{
		return m_Textures[buffer];
	}

	void Framebuffer::CopyToScreen(ClearBuffer buffer)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Id);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glBlitFramebuffer(0, 0, GetWidth(), GetHeight(), 0, 0, Graphics::CurrentContext()->GetWidth(), Graphics::CurrentContext()->GetHeight(), (GLbitfield)buffer, GL_NEAREST);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	void Framebuffer::CreateColorTextureAttachment(const Resource<Texture2D>& texture, ColorBuffer buffer)
	{
		Bind();
		texture->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		texture->SetMagFilter(MagFilter::Linear);
		texture->SetMinFilter(MinFilter::Linear);
		texture->SetWrapMode(WrapMode::Clamp);
		glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)buffer, GL_TEXTURE_2D, texture->GetID(), 0);
		glDrawBuffer((GLenum)buffer);
		m_Textures[buffer] = texture;
	}

	void Framebuffer::CreateColorTextureAttachment(ColorBuffer buffer)
	{
		CreateColorTextureAttachment(ResourceManager::Library().CreateBlankTexture2D(GetWidth(), GetHeight(), MipmapMode::Disabled), buffer);
	}

	void Framebuffer::CreateDepthTextureAttachment(const Resource<Texture2D>& texture)
	{
		Bind();
		texture->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, texture->GetWidth(), texture->GetHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		texture->SetMagFilter(MagFilter::Linear);
		texture->SetMinFilter(MinFilter::Linear);
		texture->SetWrapMode(WrapMode::Clamp);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetID(), 0);
		m_Textures[ColorBuffer::Depth] = texture;
	}

	void Framebuffer::CreateDepthTextureAttachment()
	{
		CreateDepthTextureAttachment(ResourceManager::Library().CreateBlankTexture2D(GetWidth(), GetHeight(), MipmapMode::Disabled));
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