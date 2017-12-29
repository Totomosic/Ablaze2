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
			m_Commands.Enqueue(new RenderObjectCommand);
		}
		m_RenderQueue.Sort();
		m_Commands.ExecuteAll(*this);
		m_Method->End();
		m_Commands.Clear();
		m_RenderQueue.Clear();
	}

}