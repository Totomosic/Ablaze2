#include "MaterialBase.h"

namespace Ablaze
{

	MaterialBase::MaterialBase(const Color& color, const RenderState& renderSettings, const Resource<Shader>& shader) : Object(),
		m_BaseColor(color), m_RenderState(renderSettings), m_Shader(shader)
	{
	
	}

	MaterialBase::MaterialBase(const Color& color, const Resource<Shader>& shader, const RenderState& renderSettings) : MaterialBase(color, renderSettings, shader)
	{
	
	}

	const Color& MaterialBase::BaseColor() const
	{
		return m_BaseColor;
	}

	Color& MaterialBase::BaseColor()
	{
		return m_BaseColor;
	}

	const RenderState& MaterialBase::RenderSettings() const
	{
		return m_RenderState;
	}

	RenderState& MaterialBase::RenderSettings()
	{
		return m_RenderState;
	}

	const Resource<Shader>& MaterialBase::ActiveShader() const
	{
		return m_Shader;
	}

	Resource<Shader>& MaterialBase::ActiveShader()
	{
		return m_Shader;
	}

	void MaterialBase::Apply() const
	{
	
	}

	String MaterialBase::ToString() const
	{
		return "MaterialBase";
	}

}