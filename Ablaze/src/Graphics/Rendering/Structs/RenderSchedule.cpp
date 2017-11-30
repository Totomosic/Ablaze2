#include "RenderSchedule.h"

namespace Ablaze
{

	RenderSchedule::RenderSchedule() : Object()
	{
	
	}

	RenderSchedule::~RenderSchedule()
	{
		for (auto pass : m_RenderPasses)
		{
			delete pass;
		}
	}

	RenderPass* RenderSchedule::GetRenderPass(int index) const
	{
		return m_RenderPasses[index];
	}

	void RenderSchedule::AddRenderPass(RenderPass* pass)
	{
		m_RenderPasses.push_back(pass);
	}

	void RenderSchedule::RemoveRenderPass(int index)
	{
		m_RenderPasses.erase(m_RenderPasses.begin() + index);
	}

	void RenderSchedule::RemoveRenderPass(RenderPass* pass)
	{
		auto it = std::find(m_RenderPasses.begin(), m_RenderPasses.end(), pass);
		if (it != m_RenderPasses.end())
		{
			m_RenderPasses.erase(it);
		}
	}

	void RenderSchedule::PerformRenderPass(Renderer& renderer, RenderPass* renderPass)
	{
		renderPass->Begin();
		renderer.PerformRenderPass(*renderPass);
		renderPass->End();
	}

	void RenderSchedule::Execute(Renderer& renderer)
	{
		for (RenderPass* pass : m_RenderPasses)
		{
			PerformRenderPass(renderer, pass);
		}
	}

	String RenderSchedule::ToString() const
	{
		return "RenderSchedule";
	}

}