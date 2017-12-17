#pragma once
#include "Common.h"
#include "Graphics\Framebuffer.h"
#include "Scene\LayerMask.h"
#include "Scene\Layer.h"
#include "Scene\Scene.h"
#include "Scene\SceneManager.h"
#include "Resources\Shaders\Uniforms\__Uniforms__.h"

namespace Ablaze
{

	class RenderTexture;

	class AB_API RenderPass : public Object
	{
	private:
		String m_Name;
		LayerMask m_Layers;
		Framebuffer* m_RenderTarget;
		UniformManager m_Uniforms;

		GameObject* m_CameraOverride;

	public:
		RenderPass(const String& name, const LayerMask& layers, Framebuffer* renderTarget, GameObject* cameraOverride = nullptr);
		RenderPass(const String& name, const LayerMask& layers, GameObject* cameraOverride = nullptr); // Use default renderTarget - Window
		RenderPass(const String& name, Framebuffer* renderTarget, GameObject* cameraOverride = nullptr); // Use all layers of scene
		RenderPass(const String& name, GameObject* cameraOverride = nullptr);
		RenderPass(const String& name, RenderTexture* renderTexture);

		const String& Name() const;
		String& Name();
		const LayerMask& Layers() const;
		LayerMask& Layers();
		Framebuffer* const RenderTarget() const;
		Framebuffer* RenderTarget();
		const UniformManager& Uniforms() const;
		UniformManager& Uniforms();
		GameObject* CameraOverride() const;

		std::vector<GameObject*> GetGameObjects();

		void Begin();
		void End();

		String ToString() const override;

	};

}