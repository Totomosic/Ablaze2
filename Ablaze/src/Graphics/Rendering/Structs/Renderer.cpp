#include "Renderer.h"

namespace Ablaze
{

	Renderer::Renderer(RenderMethod* method) : Object(),
		m_RenderQueue(), m_Commands(), m_Method(method), m_CurrentRenderPass(nullptr)
	{
	
	}

	Renderer::~Renderer()
	{
		delete m_Method;
	}

	const RenderQueue& Renderer::Queue() const
	{
		return m_RenderQueue;
	}

	RenderQueue& Renderer::Queue()
	{
		return m_RenderQueue;
	}

	const CommandQueue& Renderer::Commands() const
	{
		return m_Commands;
	}

	CommandQueue& Renderer::Commands()
	{
		return m_Commands;
	}

	RenderMethod* Renderer::Method() const
	{
		return m_Method;
	}

	RenderPass* Renderer::CurrentRenderPass() const
	{
		return m_CurrentRenderPass;
	}

	void Renderer::ApplyRenderOrder(RenderOrder order)
	{
		// TODO: sorting
	}

	void Renderer::SetRenderMethod(RenderMethod* method)
	{
		m_Method = method;
	}

	void Renderer::RenderNextGameObject()
	{
		GameObject* obj = Queue().Next();
		m_Method->Render(obj, obj->GetLayer()->GetActiveCamera());
	}

	String Renderer::ToString() const
	{
		return "Renderer";
	}

}