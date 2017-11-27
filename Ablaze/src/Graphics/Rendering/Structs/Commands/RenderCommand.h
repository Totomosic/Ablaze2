#pragma once
#include "Common.h"
#include "Graphics\Rendering\Structs\Renderer.h"

namespace Ablaze
{

	class AB_API RenderCommand : public Object
	{
	public:
		virtual void Execute(Renderer& renderer) = 0;

	};

}