#pragma once
#include "Graphics\Rendering\Structs\__Structs__.h"
#include "Methods\__Methods__.h"

namespace Ablaze
{

	class AB_API ForwardRenderer : public Renderer
	{
	public:
		ForwardRenderer();

		void PerformRenderPass(RenderPass& renderPass) override;

	};

}