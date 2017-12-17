#pragma once
#include "Common.h"
#include "Texture2D.h"
#include "Graphics\Framebuffer.h"
#include "Scene\LayerMask.h"

namespace Ablaze
{

	enum class CreateMode
	{
		Repeat,
		Once
	};

	// Class that represents a dynamically created texture, rendered from the scene
	class AB_API RenderTexture : public Texture2D
	{
	private:
		LayerMask m_Layers;
		GameObject* m_Camera;
		CreateMode m_Mode;
		ColorBuffer m_Buffer;

		Framebuffer m_Framebuffer;
		
	public:
		RenderTexture(int width, int height, const LayerMask& layers, GameObject* camera, CreateMode mode = CreateMode::Repeat, ColorBuffer buffer = ColorBuffer::Color0);
		RenderTexture(int width, int height, GameObject* camera, CreateMode mode = CreateMode::Repeat, ColorBuffer buffer = ColorBuffer::Color0);
		RenderTexture(int width, int height, const LayerMask& layers, CreateMode mode = CreateMode::Repeat, ColorBuffer buffer = ColorBuffer::Color0);
		RenderTexture(int width, int height, CreateMode mode = CreateMode::Repeat, ColorBuffer buffer = ColorBuffer::Color0); // Use the correct camera for the object

		const LayerMask& Layers() const;
		LayerMask& Layers();
		GameObject* Camera() const;
		const CreateMode& Mode() const;
		CreateMode& Mode();

		const Framebuffer& RenderTarget() const;
		Framebuffer& RenderTarget();

	};

}