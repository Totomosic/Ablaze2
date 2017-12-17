#include "RenderTexture.h"

namespace Ablaze
{

	RenderTexture::RenderTexture(int width, int height, const LayerMask& layers, GameObject* camera, CreateMode mode, ColorBuffer buffer) : Texture2D(width, height, ImageFormat::Rgba, MipmapMode::Enabled),
		m_Layers(layers), m_Camera(camera), m_Mode(mode), m_Framebuffer(Framebuffer(width, height, false))
	{
		if (buffer == ColorBuffer::Depth)
		{
			m_Framebuffer.CreateColorTextureAttachment();
			m_Framebuffer.CreateDepthTextureAttachment(this);
		}
		else
		{
			m_Framebuffer.CreateColorTextureAttachment(this, buffer);
			m_Framebuffer.CreateDepthTextureAttachment();
		}
	}

	RenderTexture::RenderTexture(int width, int height, GameObject* camera, CreateMode mode, ColorBuffer buffer) : RenderTexture(width, height, LayerMask(), camera, mode, buffer)
	{
	
	}

	RenderTexture::RenderTexture(int width, int height, const LayerMask& layers, CreateMode mode, ColorBuffer buffer) : RenderTexture(width, height, layers, nullptr, mode, buffer)
	{
	
	}

	RenderTexture::RenderTexture(int width, int height, CreateMode mode, ColorBuffer buffer) : RenderTexture(width, height, nullptr, mode, buffer)
	{
	
	}

	const LayerMask& RenderTexture::Layers() const
	{
		return m_Layers;
	}

	LayerMask& RenderTexture::Layers()
	{
		return m_Layers;
	}

	GameObject* RenderTexture::Camera() const
	{
		return m_Camera;
	}

	const CreateMode& RenderTexture::Mode() const
	{
		return m_Mode;
	}

	CreateMode& RenderTexture::Mode()
	{
		return m_Mode;
	}

	const Framebuffer& RenderTexture::RenderTarget() const
	{
		return m_Framebuffer;
	}

	Framebuffer& RenderTexture::RenderTarget()
	{
		return m_Framebuffer;
	}

}