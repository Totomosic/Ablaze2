#pragma once
#include "Common.h"
#include "Resources\Asset.h"
#include "RenderState.h"
#include "Resources\Shaders\Shader.h"
#include "Resources\Shaders\Uniforms\__Uniforms__.h"

namespace Ablaze
{

	class AB_API MaterialBase : public Object
	{
	protected:
		Color m_BaseColor;
		RenderState m_RenderState;
		Shader* m_Shader;
		UniformManager m_Uniforms;

	public:
		MaterialBase(const Color& color, const RenderState& renderSettings, Shader* shader);
		MaterialBase(const Color& color, Shader* shader, const RenderState& renderSettings = RenderState());

		const Color& BaseColor() const;
		Color& BaseColor();
		const RenderState& RenderSettings() const;
		RenderState& RenderSettings();
		Shader* ActiveShader() const;
		const UniformManager& Uniforms() const;
		UniformManager& Uniforms();

		virtual void Apply() const;
		String ToString() const override;
		virtual MaterialBase* Clone() const = 0;
		virtual void Serialize(JSONwriter& writer) const;

	};

}