#include "ForwardRenderer.h"

namespace Ablaze
{

	ForwardRenderer::ForwardRenderer(RenderOrder order) : Renderer(new ForwardRenderMethod, order)
	{
		
	}

	void ForwardRenderer::PerformRenderPass(RenderPass& pass)
	{
		m_CurrentRenderPass = &pass;
		m_Method->Begin();
		for (GameObject* object : pass.GetGameObjects())
		{
			m_RenderQueue.Enqueue(object);
		}
		m_RenderQueue.Sort();
		while (m_RenderQueue.Size() > 0)
		{
			RenderNextGameObject();
		}
		m_Method->End();
		m_RenderQueue.Clear();
	}

}