#pragma once
#include "RenderCommand.h"

namespace Ablaze
{

	class AB_API RenderObjectCommand : public RenderCommand
	{
	public:
		void Execute(Renderer& renderer) override;

		String ToString() const override;

	};

}