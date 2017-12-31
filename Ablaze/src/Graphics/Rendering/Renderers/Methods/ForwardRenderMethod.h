#pragma once
#include "Graphics\Rendering\Structs\RenderMethod.h"
#include "Scene\Components\__Components__.h"

namespace Ablaze
{

	class ForwardRenderMethod : public RenderMethod
	{
	private:
		Material m_CurrentMaterial;

	public:
		ForwardRenderMethod();

		void Begin() override;
		void Render(GameObject* object, GameObject* camera) override;
		void End() override;

		String ToString() const override;

	};

}