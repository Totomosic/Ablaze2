#pragma once
#include "Common.h"
#include "Scene\LayerMask.h"
#include "Resources\Shaders\Uniforms\__Uniforms__.h"

namespace Ablaze
{

	class AB_API RenderPass : public Object
	{
	private:
		String m_Name;
		LayerMask m_Layers;
		Framebuffer* m_RenderTarget;
		UniformManager m_Uniforms;

	public:
		RenderPass(const String& name, const LayerMask& layers, Framebuffer* renderTarget);
		RenderPass(const String& name, const LayerMask& layers); // Use default renderTarget - Window
		RenderPass(const String& name, Framebuffer* renderTarget); // Use all layers of scene
		RenderPass(const String& name);

		const String& Name() const;
		String& Name();
		const LayerMask& Layers() const;
		LayerMask& Layers();
		Framebuffer* const RenderTarget() const;
		Framebuffer* RenderTarget();
		const UniformManager& Uniforms() const;
		UniformManager& Uniforms();

		String ToString() const override;

	};

}