#pragma once
#include "Common.h"
#include "Scene\GameObject.h"

namespace Ablaze
{

	// Object that describes how to render a single object
	class AB_API RenderMethod : public Object
	{
	public:
		virtual void Begin() = 0; // Called at beginning of each render pass
		virtual void Render(GameObject* object, GameObject* camera) = 0; // May need to accept parameters such as the current renderer?
		virtual void End() = 0; // Called at end of each render pass

	};

}