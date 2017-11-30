#pragma once
#include "Common.h"
#include "RenderPass.h"
#include "Renderer.h"

namespace Ablaze
{

	class AB_API RenderSchedule : public Object
	{
	private:
		std::vector<RenderPass*> m_RenderPasses;

	public:
		RenderSchedule();
		~RenderSchedule();

		RenderPass* GetRenderPass(int index) const;

		void AddRenderPass(RenderPass* pass);
		void RemoveRenderPass(RenderPass* pass);
		void RemoveRenderPass(int index);

		void PerformRenderPass(Renderer& renderer, RenderPass* pass);
		void Execute(Renderer& renderer);

		String ToString() const override;

	};

}