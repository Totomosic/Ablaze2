#pragma once
#include "Common.h"
#include "structs\__structs__.h"

namespace Ablaze
{

	enum class ClearBuffer
	{
		Color = GL_COLOR_BUFFER_BIT,
		Depth = GL_DEPTH_BUFFER_BIT,
		Stencil = GL_STENCIL_BUFFER_BIT
	};

	inline ClearBuffer operator|(ClearBuffer c1, ClearBuffer c2)
	{
		return (ClearBuffer)((int)c1 | (int)c2);
	}

	class AB_API Framebuffer : public GLObject
	{
	private:
		static const Framebuffer* s_CurrentlyBound;

	private:
		Viewport m_Viewport;
		Color m_ClearColor;

	private:
		Framebuffer(int width, int height, bool window); // Window Framebuffer constructor

	public:
		Framebuffer(int width, int height, const Color& clearColor = Color::Black());
		~Framebuffer() override;

		const Color& GetClearColor() const;
		int GetWidth() const;
		int GetHeight() const;
		float GetAspect() const;
		const Viewport& GetViewport() const;

		void Clear(ClearBuffer buffer = ClearBuffer::Color | ClearBuffer::Depth) const;
		void Bind() const override;
		void Unbind() const override;

		void SetClearColor(const Color& clearColor);
		void SetWidth(int width);
		void SetHeight(int height);

		String ToString() const override;

		friend class Window;

	private:
		static Framebuffer* WindowFramebuffer(int width, int height);

	};

}