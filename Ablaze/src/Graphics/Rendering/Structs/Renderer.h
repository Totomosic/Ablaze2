#pragma once
#include "Common.h"
#include "Commands\CommandQueue.h"
#include "RenderQueue.h"
#include "RenderMethod.h"
#include "RenderPass.h"

namespace Ablaze
{

	class AB_API Renderer : public Object
	{
	private:
		RenderQueue m_RenderQueue;
		CommandQueue m_Commands;
		RenderMethod* m_Method;
		RenderPass* m_CurrentRenderPass;

	public:
		Renderer(RenderMethod* renderMethod);
		virtual ~Renderer();

		const RenderQueue& Queue() const;
		RenderQueue& Queue();
		const CommandQueue& Commands() const;
		CommandQueue& Commands();
		RenderMethod* Method() const;
		RenderPass* CurrentRenderPass() const;

		virtual void ApplyRenderOrder(RenderOrder order);
		virtual void SetRenderMethod(RenderMethod* method);

		virtual void PerformPass(RenderPass& renderPass) = 0;
		virtual void RenderNextGameObject(GameObject* object); // Called by RenderObject command

		String ToString() const override;

	};

}