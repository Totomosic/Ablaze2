#pragma once
#include "Common.h"
#include "Resources\Asset.h"
#include "RenderState.h"
#include "Resources\Shaders\Shader.h"

namespace Ablaze
{

	template<typename> class Resource;

	class AB_API MaterialBase : public Object
	{
	protected:
		Color m_BaseColor;
		RenderState m_RenderState;
		Resource<Shader> m_Shader;

	public:
		MaterialBase(const Color& color, const RenderState& renderSettings, const Resource<Shader>& shader);
		MaterialBase(const Color& color, const Resource<Shader>& shader, const RenderState& renderSettings = RenderState());

		const Color& BaseColor() const;
		Color& BaseColor();
		const RenderState& RenderSettings() const;
		RenderState& RenderSettings();
		const Resource<Shader>& ActiveShader() const;
		Resource<Shader>& ActiveShader();

		virtual void Apply() const;
		String ToString() const override;
		virtual MaterialBase* Clone() const = 0;

	};

}