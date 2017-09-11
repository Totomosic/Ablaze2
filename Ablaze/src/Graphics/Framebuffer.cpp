#include "Framebuffer.h"

namespace Ablaze
{

	const Framebuffer* Framebuffer::s_CurrentlyBound = nullptr;

	Framebuffer::Framebuffer(int width, int height, bool window)
		: m_Viewport(Viewport(width, height)), m_ClearColor(Color::Black())
	{
	
	}

	Framebuffer::Framebuffer(int width, int height, const Color& clearColor)
		: m_Viewport(Viewport(width, height)), m_ClearColor(clearColor)
	{
		glGenFramebuffers(1, &m_Id);
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

	String Framebuffer::ToString() const
	{
		return "Framebuffer";
	}

	Framebuffer* Framebuffer::WindowFramebuffer(int width, int height)
	{
		return new Framebuffer(width, height, true);
	}

}