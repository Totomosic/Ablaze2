#pragma once
#include "Common.h"
#include "structs\__structs__.h"
#include "Resources\Textures\Texture2D.h"

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

	enum class ColorBuffer : GLenum
	{
		Color0 = GL_COLOR_ATTACHMENT0,
		Color1 = GL_COLOR_ATTACHMENT1,
		Color2 = GL_COLOR_ATTACHMENT2,
		Color3 = GL_COLOR_ATTACHMENT3,
		Color4 = GL_COLOR_ATTACHMENT4,
		Color5 = GL_COLOR_ATTACHMENT5,

		Depth = GL_DEPTH_ATTACHMENT
	};

	enum class Filter : GLenum
	{
		Linear = GL_LINEAR,
		Nearest = GL_NEAREST
	};

	class AB_API Framebuffer : public GLObject
	{
	private:
		Viewport m_Viewport;
		Color m_ClearColor;
		std::unordered_map<ColorBuffer, Texture2D*> m_Textures;

	private:
		Framebuffer(int width, int height); // Window Framebuffer constructor

	public:
		Framebuffer(int width, int height, bool createOnLoad, const Color& clearColor = Color::Black());
		~Framebuffer() override;

		const Color& GetClearColor() const;
		int Width() const;
		int Height() const;
		float GetAspect() const;
		const Viewport& GetViewport() const;
		Viewport& GetViewport();

		void Clear(ClearBuffer buffer = ClearBuffer::Color | ClearBuffer::Depth) const;
		void Bind() const override;
		void Unbind() const override;

		void SetClearColor(const Color& clearColor);

		Texture2D* GetTexture(ColorBuffer buffer) const;

		void CopyToScreen(ClearBuffer buffer = ClearBuffer::Color | ClearBuffer::Depth, Filter filter = Filter::Nearest, ColorBuffer readBuffer = ColorBuffer::Color0) const;
		void CreateColorTextureAttachment(Texture2D* texture, ColorBuffer buffer = ColorBuffer::Color0);
		void CreateColorTextureAttachment(ColorBuffer buffer = ColorBuffer::Color0);
		void CreateDepthTextureAttachment(Texture2D* texture);
		void CreateDepthTextureAttachment();

		String ToString() const override;

		friend class Window;

	private:
		static Framebuffer* WindowFramebuffer(int width, int height);

	};

}