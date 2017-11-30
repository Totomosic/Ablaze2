#include "RenderObjectCommand.h"

namespace Ablaze
{

	void RenderObjectCommand::Execute(Renderer& renderer)
	{
		renderer.RenderNextGameObject();
	}

	String RenderObjectCommand::ToString() const
	{
		return "RenderObjectCommand";
	}

}