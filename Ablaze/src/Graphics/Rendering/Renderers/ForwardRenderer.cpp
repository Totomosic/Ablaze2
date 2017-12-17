#include "ForwardRenderer.h"

namespace Ablaze
{

	ForwardRenderer::ForwardRenderer() : Renderer(new ForwardRenderMethod)
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
		m_Commands.ExecuteAll(*this);
		m_Method->End();
		m_Commands.Clear();
		m_RenderQueue.Clear();
	}

}