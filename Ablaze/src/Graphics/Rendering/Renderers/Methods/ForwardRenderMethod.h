#pragma once
#include "Graphics\Rendering\Structs\RenderMethod.h"
#include "Scene\Components\__Components__.h"

namespace Ablaze
{

	class ForwardRenderMethod : public RenderMethod
	{
	public:
		void Begin() override;
		void Render(GameObject* object, GameObject* camera) override;
		void End() override;

		String ToString() const override;

	};

}