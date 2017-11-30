#include "RenderPass.h"
#include "Graphics\Rendering\Graphics.h"
#include "Scene\ComponentSet.h"

namespace Ablaze
{
	
	RenderPass::RenderPass(const String& name, const LayerMask& layers, Framebuffer* renderTarget) : Object(),
		m_Name(name), m_Layers(layers), m_RenderTarget(renderTarget), m_Uniforms()
	{
	
	}

	RenderPass::RenderPass(const String& name, const LayerMask& layers) : RenderPass(name, layers, &Graphics::CurrentContext()->GetFramebuffer())
	{
	
	}

	RenderPass::RenderPass(const String& name, Framebuffer* renderTarget) : RenderPass(name, LayerMask(true), renderTarget)
	{
	
	}

	RenderPass::RenderPass(const String& name) : RenderPass(name, LayerMask(true))
	{
	
	}

	const String& RenderPass::Name() const
	{
		return m_Name;
	}

	String& RenderPass::Name()
	{
		return m_Name;
	}

	const LayerMask& RenderPass::Layers() const
	{
		return m_Layers;
	}

	LayerMask& RenderPass::Layers()
	{
		return m_Layers;
	}

	Framebuffer* const RenderPass::RenderTarget() const
	{
		return m_RenderTarget;
	}

	Framebuffer* RenderPass::RenderTarget()
	{
		return m_RenderTarget;
	}

	const UniformManager& RenderPass::Uniforms() const
	{
		return m_Uniforms;
	}

	UniformManager& RenderPass::Uniforms()
	{
		return m_Uniforms;
	}

	std::vector<GameObject*> RenderPass::GetGameObjects()
	{
		std::vector<GameObject*> objects;
		if (SceneManager::Instance().HasScene() && SceneManager::Instance().CurrentScene().HasLayer())
		{
			for (Layer* layer : SceneManager::Instance().CurrentScene().GetLayers(m_Layers))
			{
				for (GameObject* object : layer->GameObjects())
				{
					if (object->HasComponent<Transform>() && object->HasComponent<Mesh>())
					{
						objects.push_back(object);
					}
				}
			}
		}
		return objects;
	}

	void RenderPass::Begin()
	{
		m_RenderTarget->Bind();
		m_RenderTarget->Clear();
	}

	void RenderPass::End()
	{
		
	}

	String RenderPass::ToString() const
	{
		return "RenderPass";
	}

}